Descriptions:
Initiator.c - the program that is meant to be ran
Pell.c: writes the nth pell number to the shared memory given as an argument
Composite.c: writes the nth composite number to the shared memory given as an argument
Total.c: writes the sum from 0 -> n to the shared memory given as an argument
Reader.c: takes a file and a pipe as arguments and writes the sum of all the values in the file to the pipe
** Shared.h ** - contains the methods and headers that I used in more than 1 of my programs to keep my code DRY
Makefile - make creates Reader, Pell, Composite, Total, and Initiator executables. Make clean removes all five executables. make package packages the code.
README.txt - file containing a description of each file and any information you feel the grader
needs to grade your program, and answers for the 4 questions

ANSWERS:
1. pipe()
2. fd[0] - read, fd[1] - write
3. mmap()
4. shm_open() returns a file descriptor
