



#*****************************************************************************
# File: Makefile
# Author: Naveen Fernando
# Student ID: 21765018
# Unit: COMP2002 Unix Systems Programming (Semester 1, 2025)
# Date Created: 27/04/2025
# Last Modified: 6/05/2025
#
# Description:
# This Makefile compiles the Prime program.
# Usage: make
#*****************************************************************************


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g 
LDFLAGS = -lm 

# Files
OBJ = prime.o fileReader.o utils.o
EXEC = prime

# Build + clean object files after linking
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)
	rm -f $(OBJ)

# Compile prime.o
prime.o: prime.c fileReader.h utils.h
	$(CC) -c prime.c $(CFLAGS)

# Compile fileReader.o
fileReader.o: fileReader.c fileReader.h utils.h
	$(CC) -c fileReader.c $(CFLAGS)

# Compile utils.o
utils.o: utils.c utils.h
	$(CC) -c utils.c $(CFLAGS)

# Clean 
clean:
	rm -f $(EXEC) $(OBJ)
