/*****************************************************************************
 * File: prime.c
 * Author: Naveen Fernando
 * Date Created: 30/04/2025
 * Last Modified: 05/05/2025
 *
 * Description:
 * This program reads integers from a text file and checks each for primality
 * using child processes. Each child tests one number and sends the result
 * back to the parent through pipes. The parent prints the results.
 *
 * Dependencies:
 * - fileReader.h
 * - utils.h
 *
 * Assumptions:
 * - The input file contains valid integers.    
 * - The input file does not contain negative numbers.
 * - The integers are <= 2147483647.
 * 
 *****************************************************************************/


#include <unistd.h>    
#include <fcntl.h>      
#include <stdlib.h>     
#include <sys/wait.h>  
#include <math.h>       
#include <errno.h>      
#include <time.h>       

#include "fileReader.h"
#include "utils.h"






// Struct to hold child ID and result back to parent
typedef struct 
{
    int child_id;
    int result;  // 1 = prime, 0 = not prime

} ResultPacket;


/***************************************************************************************
 * Function: main
 *
 * Entry point. Reads integers from a file, creates child processes for primality
 * testing, and uses pipes for communication. Outputs the results.
 *
 * 
 * Returns:
 *   - 0 on success, exits on error.
 *
 **************************************************************************************/

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        char msg[] = "Usage: ./prime <file_name>\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
        exit(1);
    }

    // Read numbers from file
    NumberData data = read_numbers_from_file(argv[1]);
    int *numbers = data.numbers;
    int num_count = data.count;

    
    
   
    // Create pipes
    int p2c[num_count][2];  // Parent to Child
    int c2p[num_count][2];  // Child to Parent

    for (int i = 0; i < num_count; i++) {
        if (pipe(p2c[i]) == -1 || pipe(c2p[i]) == -1) 
        {
            char msg[] = "Pipe creation failed\n";
            write(STDERR_FILENO, msg, sizeof(msg) - 1);
            free(numbers);
            exit(1);
        }
    }

    pid_t pids[num_count]; // Child process IDs for wait

    // Create child processes and send numbers
    for (int i = 0; i < num_count; i++) 
    {
        
        pid_t pid = fork();
        if (pid == -1) 
        {
            char msg[] = "Fork failed\n";
            write(STDERR_FILENO, msg, sizeof(msg) - 1);
            free(numbers);
            exit(1);
        }

        
        if (pid == 0) // Child
        {
            // Close unrelevant pipe ends of other children
            for (int j = 0; j < num_count; j++) 
            {
                if (j != i) 
                {
                    close(p2c[j][0]); close(p2c[j][1]);
                    close(c2p[j][0]); close(c2p[j][1]);
                }
            }

            // close unused pipe ends 
            close(p2c[i][1]); // closes write end of p2c 
            close(c2p[i][0]); // closes read end of c2p

            

            int num;

            // reads number sent by parent
            if (read(p2c[i][0], &num, sizeof(int)) <= 0) 
            {
                char msg[] = "Child failed to read number\n";
                write(STDERR_FILENO, msg, sizeof(msg) - 1);
                close(p2c[i][0]);
                close(c2p[i][1]);
                exit(1);
            }

            close(p2c[i][0]);// closes the read end after reading

            // Perform primality Test
            int isprime = is_prime(num); 

            
            ResultPacket packet;
            packet.child_id = i;
            packet.result = isprime;

            // Send result back to parent
            write(c2p[i][1], &packet, sizeof(ResultPacket));
            close(c2p[i][1]); // closes write end of c2p
            exit(0); // exit child
        } 
        else 
        {
            pids[i] = pid; // store pid
        }

    }

    // Parent: Send numbers to each child
    for (int i = 0; i < num_count; i++) 
    {
        close(p2c[i][0]); // closes read end of p2c by parent
        close(c2p[i][1]); //

        int num_to_send = numbers[i];  

        write(p2c[i][1], &num_to_send, sizeof(int));
        close(p2c[i][1]);
    }

    // Parent Wait and receive results
    for (int i = 0; i < num_count; i++) 
    {
        int status;
        pid_t ended_pid = wait(&status);
        if (ended_pid == -1) 
        {
            char msg[] = "wait() failed\n";
            write(STDERR_FILENO, msg, sizeof(msg) - 1);
            continue;
        }


        int index = -1;
        for (int j = 0; j < num_count; j++) 
        {
            if (pids[j] == ended_pid) 
            {
                index = j;
                break;
            }
        }

        if (index != -1) 
        {
            ResultPacket packet;
            if (read(c2p[index][0], &packet, sizeof(ResultPacket)) > 0) 
            {
                char part1[] = "Child "; 
                char id_str[20];
                char part2[] = " completed the task: ";
                char num_str[20];
                char part3[] = " is a Prime number\n";
                char part3_not[] = " is NOT a Prime number\n";

                int_to_string(packet.child_id, id_str); 
                int_to_string(numbers[packet.child_id], num_str);//

                write(STDOUT_FILENO, part1, sizeof(part1) - 1);
                write(STDOUT_FILENO, id_str, string_length(id_str));
                write(STDOUT_FILENO, part2, sizeof(part2) - 1);
                write(STDOUT_FILENO, num_str, string_length(num_str));
                if (packet.result == 1) 
                {
                    write(STDOUT_FILENO, part3, sizeof(part3) - 1);
                } 
                else 
                {
                    write(STDOUT_FILENO, part3_not, sizeof(part3_not) - 1);
                }
            }

            close(c2p[index][0]); // Close the pipe c2p
        }
    }

    
    free(numbers);
    return 0;
}
