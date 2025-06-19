
/*****************************************************************************
 * File: utils.c
 * Author: Naveen Fernando
 * Date Created: 30/04/2025
 * Last Modified: 06/05/2025
 *
 * Description:
 * This file provides utility functions including:
 * - Integer parsing and string conversion.
 * - String length calculation.
 * - Primality testing with simulated delay.
 * - Sleeping for 1 millisecond.
 *
 * Dependencies:
 * - utils.h
 * 
 * 
 * Assumptions:
 * - The input file contains valid integers.
 * - The input file does not contain negative numbers.
 * - The integers are <= 2147483647.
 * 
 * References:
 * - Unix and C programming (COMP1000) Assignment Resources 
 * - https://www.geeksforgeeks.org/trial-division-algorithm-for-prime-factorization/
 *
 *****************************************************************************/
#define _POSIX_C_SOURCE 199309L 
#include <unistd.h>  
#include <stdlib.h>  
#include <time.h>   
#include <math.h>   
#include "utils.h"

/***************************************************************************************
 * Function: sleep_one_millisecond
 *
 * Sleeps for 1 millisecond using nanosleep().
 * Reference : Unix and C programming (COMP1000) Assignment Resources
 *
 **************************************************************************************/
void sleep_one_millisecond(void) 
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000;  // 1 millisecond
    nanosleep(&ts, NULL);
}

/***************************************************************************************
 * Function: is_prime
 *
 * Checks if a number is prime using trial division.
 * Sleeps 1ms per iteration to simulate delay.
 * 
 * How it works:
 *   - If n is less than 2, it is not prime.
 *   - If n is 2, it is prime.
 *   - If n is even, it is not prime.
 *   - For odd n , it assumes n is prime and checks divisibility for odd numbers up to sqrt(n).
 *   - If n is divisible by any odd number, it is not prime.
 * 
 * Reference : https://www.geeksforgeeks.org/trial-division-algorithm-for-prime-factorization/
 *           - Convereted the original code which was in C++ to C and used C system calls and math.h (sqrt)
 *           - skipped all even numbers after checking for n % 2 == 0
 *           - added sleep_one_millisecond() in each iteration to simulate delay
 *
 **************************************************************************************/

 int is_prime(int n) 
 {
    int result = 1;
    if (n < 2) 
    {
        result = 0;
    } 
    else if (n == 2) 
    {
        result = 1;
    } 
    else if (n % 2 == 0) // checks if n is even
    {
        result = 0;
    } 
    else 
    {
        result = 1;  // Assume prime
        int limit = (int)sqrt((double)n); //calculate the square root of n and convert it to an integer
        for (int i = 3; i <= limit; i += 2) // checks if i is odd
        {
            sleep_one_millisecond(); // simulate delay (1ms)
            if (n % i == 0) 
            {
                result = 0;
                break;
            }
        }
    }
    

    return result;
}


/***************************************************************************************
 * Function: parse_int
 *
 * Converts a numeric string to an integer.
 *
 * Parameters:
 *   - str: input string to convert.
 *
 * Returns:
 *   - Parsed integer value.
 *
 **************************************************************************************/

int parse_int(char *str) 
{
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) //  checks if str[i] is not null
    {
        if (str[i] < '0' || str[i] > '9') // checks if str[i] is a digit
        {
            char msg[] = "Error: Invalid character in number string\n";
            write(STDERR_FILENO, msg, sizeof(msg) - 1);
            exit(1);
        }
        result = result * 10 + (str[i] - '0'); // multiply by 10 to shift the decimal places
    }
    return result;
}


/***************************************************************************************
 * Function: int_to_string
 *
 * Converts an integer to a string. This works by first converting the integer to a string in reverse order, 
 * then reversing the string to get the correct order. 
 * The function handles the special case where num is 0. The resulting string is null-terminated
 *
 * Parameters:
 *   - num: the integer to convert.
 *   - str: buffer to store the resulting string.
 * 
 * 
 *
 **************************************************************************************/

void int_to_string(int num, char *str) 
{
    int i = 0, j;
    char temp_str[20]; // temp array to hold the string in reverse

    if (num == 0) 
    {
        str[i++] = '0'; //set str[0] to '0'
        str[i] = '\0'; // add null-terminator
        return;
    }

    // convert num to string in reverse
    while (num > 0) 
    {
        temp_str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    // reverse the string to the correct order
    for (j = 0; j < i; j++) 
    {
        str[j] = temp_str[i - j - 1];
    }
    str[i] = '\0'; // add null-terminator
}

/***************************************************************************************
 * Function: string_length
 *
 * Calculates the length of a string (null-terminated).
 *
 * Parameters:
 *   - str: input string.
 *
 * Returns:
 *   - Length of the string.
 *
 **************************************************************************************/

int string_length (char *str) 
{
    int len = 0;
    while (str[len] != '\0') // Find the null-terminator
    {
        len++; 
    }
    return len; 
}


