/*****************************************************************************
 * File: utils.h
 * Author: Naveen Fernando
 * Student ID: 21765018
 * Unit: COMP2002 Unix Systems Programming (Semester 1, 2025)
 * Date Created: 30/04/2025
 * Last Modified: 07/05/2025
 *
 * Description:
 * Header file for utility functions:
 * - Integer parsing/conversion.
 * - String length.
 * - Prime checking and delay simulation.
 *
 *****************************************************************************/


#ifndef UTILS_H
#define UTILS_H

void int_to_string(int num, char *str);
int parse_int(char *str);
int string_length(char *str);
void sleep_one_millisecond(void);
int is_prime(int n);

#endif
