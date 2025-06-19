/*****************************************************************************
 * File: fileReader.h
 * Author: Naveen Fernando
 * Student ID: 21765018
 * Unit: COMP2002 Unix Systems Programming (Semester 1, 2025)
 * Date Created: 30/04/2025
 * Last Modified: 05/05/2025
 *
 * Description:
 * This header defines the NumberData struct and the function prototype 
 * for reading integers from a file into a dynamically allocated array.
 *
 *****************************************************************************/

 #ifndef FILEREADERH
 #define FILEREADERH
 
 // Struct to hold the array of numbers and the count
 typedef struct 
 {
     int *numbers;  // pointer to the integer array
     int count;     // total numbers read from the file

 } NumberData;
 
 // Reads integers from a file and returns them in NumberData
 NumberData read_numbers_from_file(const char *filename);
 
 #endif
 




 

