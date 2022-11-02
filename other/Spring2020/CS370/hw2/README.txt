Starter[1898741] : Forked process with ID 1898742.
Starter[1898741]: waiting for process [1898742].
Fibb[1898742] : Number of terms in fibonacii series is 5
Fibb[1898742] : The first 5 numbers of the Fibonacci sequence are:
0, 0, 1, 2, 3, 
Starter: Child process 1898742 returned 3.
Starter[1898741] : Forked process with ID 1898743.
Starter[1898741]: waiting for process [1898743].
Prime[1898743] : First 5 prime numbers are:
2, 3, 5, 7, 11, 
Starter: Child process 1898743 returned 11.
Starter[1898741] : Forked process with ID 1898744.
Starter[1898741]: waiting for process [1898744].
Total[1898744] : Sum = 15
Starter: Child process 1898744 returned 15.
Starter[1898741] : Forked process with ID 1898745.
Starter[1898741]: waiting for process [1898745].
Fibb[1898745] : Number of terms in fibonacii series is 14
Fibb[1898745] : The first 14 numbers of the Fibonacci sequence are:
0, 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 
Starter: Child process 1898745 returned 233.
Starter[1898741] : Forked process with ID 1898746.
Starter[1898741]: waiting for process [1898746].
Prime[1898746] : First 14 prime numbers are:
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 
Starter: Child process 1898746 returned 43.
Starter[1898741] : Forked process with ID 1898747.
Starter[1898741]: waiting for process [1898747].
Total[1898747] : Sum = 105
Starter: Child process 1898747 returned 105.
fibb: 233
Prime: 29
total Count: 55

Descriptions:
Fibb.c: contains a method that runs the fibonacci code and int main that calls it
Prime.c: contains a method that runs code to calculate prime numbers and int main that calls it
Total.c: contains a method that runs code to do what Total.c is meant to do and an int main that calls it
Starter.c: contains a function that runs any single process and an int main that calls the function on all three other programs
Makefile: make build or make creates Fibb, Prime, Total, and Starter executables. Make clean removes all four executables. make package packages the code.
README.txt: answers questions, provides example output and descriptions of each file

Questions:
1. 8 bits
2. <sys/wait.h>
3. fork() returns 0 to the child process and returns the child process's ID to parent process
4. the number of processes your system allows you to create has been exceeded.
5. We are doing sequential processing.
6. No