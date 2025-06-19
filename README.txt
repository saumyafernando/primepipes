Auther Name: Naveen Fernando


---------------------------Prime Number Checker---------------------

-------------------------------Description--------------------------

  This project implements a Prime Number Checker using Unix Systems Programming concepts. 
  The program reads a list of integers from a text file and checks if each number is prime using child processes.
  Each child receives a number from the parent process through a pipe, performs the primality test, and returns the result back via another pipe.
  The parent collects results and displays them.
 
  The implementation uses system calls like fork(), pipe(), read(), write(), and wait(). 
  The program avoids using standard C library functions like fscanf() or printf() for file and I/O handling.


-----------------------------File Structure-------------------------

├── prime.c           # Main program (process creation & coordination)  
├── fileReader.c      # Reads integers from file  
├── fileReader.h      # Header for file reading  
├── utils.c           # Utility functions (parse_int, int_to_string, etc.)  
├── utils.h           # Header for utils  
├── Makefile          # For building the program  
├── numbers.txt       # Sample input file  
├── Report.txt        # Design report Answering the Questions  
└── README.txt        # This file  



-----------------------How to Compile & Run-------------------------

--To Compile--

make

- This will compile all `.c` files and link them into an executable `prime`.



-- To Run the Program--

./prime numbers.txt

-  Where `numbers.txt` is the input file. The first line of the file should contain the count of numbers, and the following lines should list the integers you want to check, like this:

4  
23  
87  
19  
90



--------------------------- Sample Output----------------------------

./prime numbers.txt  
Child 0 completed the task: 7 is a Prime number  
Child 1 completed the task: 20 is NOT a Prime number  
Child 3 completed the task: 3849214 is NOT a Prime number  
Child 4 completed the task: 19 is a Prime number  
Child 2 completed the task: 11 is a Prime number  
Child 6 completed the task: 99991 is a Prime number  
Child 7 completed the task: 104729 is a Prime number  
Child 8 completed the task: 1299709 is a Prime number  
Child 9 completed the task: 15485863 is a Prime number  
Child 10 completed the task: 32452843 is a Prime number  
Child 11 completed the task: 49979687 is a Prime number  
Child 5 completed the task: 67867967 is a Prime number  

------------------------Reference-----------------------------

- Unix and C programming (COMP1000) Assignment Resources  
- https://www.geeksforgeeks.org/trial-division-algorithm-for-prime-factorization/  
- https://www.geeksforgeeks.org/write-your-own-atoi/
