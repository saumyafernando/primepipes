
/*****************************************************************************
 * File: fileReader.c
 * Author: Naveen Fernando
 * Student ID: 21765018
 * Unit: COMP2002 Unix Systems Programming (Semester 1, 2025)
 * Date Created: 30/04/2025
 * Last Modified: 5/05/2025
 *
 * Description:
 * This file implements the read_numbers_from_file() function, which reads
 * integers from a text file into a dynamically allocated array and returns 
 * them using a NumberData struct. The input file specifies the count of numbers 
 * in the first line, followed by the numbers (one per line).
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
 *
 *****************************************************************************/

#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include "fileReader.h" 
#include "utils.h" 

/***************************************************************************************
 * Function: read_numbers_from_file
 *
 * Reads integers from a file and returns them in a NumberData struct. The first line
 * of the file specifies how many numbers follow. Each number is on a new line.
 *
 * Parameters:
 *   - filename: the name of the file to read.
 *
 * Returns:
 *   - NumberData struct with:
 *       - numbers: array of integers.
 *       - count: how many numbers were read.
 *
 * Exits:
 *   - On file read errors and mismatched count error handling.
 *
 **************************************************************************************/

NumberData read_numbers_from_file(const char *filename) 
{
    #define BUFFER_SIZE 20 

    // Open the file
    int fd = open(filename, O_RDONLY);  
    if (fd < 0) 
    {
        char msg[] = "Failed to open file\n";
        write(STDERR_FILENO, msg, sizeof(msg) - 1);
        exit(1);
    }

    char buffer;
    char temp[BUFFER_SIZE];
    int temp_idx = 0;

    // Read the first line for the cout of numbers
    while (read(fd, &buffer, 1) > 0) 
    {
        if (buffer == '\n') 
        {
            break;
        }
        temp[temp_idx++] = buffer;
    }
    temp[temp_idx] = '\0';
    int total_numbers = parse_int(temp); 



    
    //  Memory allocation 
    int *numbers = (int *)malloc(total_numbers * sizeof(int));
    if (!numbers) 
    {
        char msg[] = "Memory allocation failed...\n";
        write(STDERR_FILENO, msg, sizeof(msg) - 1);
        close(fd);
        exit(1);
    }

    int num_count = 0;
    temp_idx = 0;

    // Read each integer 
    int ret;
    while ((ret = read(fd, &buffer, 1)) > 0) 
    {
        if (buffer == '\n') // Check for newline
        {
            temp[temp_idx] = '\0';
            numbers[num_count++] = parse_int(temp);  
            temp_idx = 0;
        } 
        else 
        {
            temp[temp_idx++] = buffer;
        }
    }

    // Handle last number if no newline at the end
    if (temp_idx > 0) 
    {
        temp[temp_idx] = '\0';
        numbers[num_count++] = parse_int(temp);
    }

    // Check for read errors
    if (ret < 0) 
    {
        char msg[] = "Error reading file...\n";
        write(STDERR_FILENO, msg, sizeof(msg) - 1);
        close(fd);
        free(numbers);
        exit(1);
    }

    close(fd);

    // Sanity check: count match
    if (num_count != total_numbers) 
    {
        char msg[] = "Mismatch between expected and actual number count\n";
        write(STDERR_FILENO, msg, sizeof(msg) - 1);
        free(numbers);
        exit(1);
    }

    

    NumberData data;
    data.numbers = numbers;
    data.count = total_numbers;  
    return data;

}
