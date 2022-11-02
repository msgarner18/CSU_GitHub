input file contains:
10
15
EXAMPLE OUTPUT:

Initiator[1596951] : Forked process with ID 1596952.
Initiator[1596951]: Waiting for Process [1596952].
Pell[1596952]: Number of terms in Pell series is 10
Pell[1596952]: The first 10 numbers of the Pell sequence are:
0, 1, 2, 5, 12, 29, 70, 169, 408, 985, 
Initiator: Child process 1596952 returned 217.
Initiator[1596951] : Forked process with ID 1596953.
Initiator[1596951]: Waiting for Process [1596953].
Composite[1596953]: First 10 composite numbers are:
4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 
Initiator: Child process 1596953 returned 18.
Initiator[1596951] : Forked process with ID 1596954.
Initiator[1596951]: Waiting for Process [1596954].
Total[1596954] : Sum = 55
Initiator: Child process 1596954 returned 55.
Pell: 217
Composite: 18
total: 55
Initiator[1596951] : Forked process with ID 1596955.
Initiator[1596951]: Waiting for Process [1596955].
Pell[1596955]: Number of terms in Pell series is 15
Pell[1596955]: The first 15 numbers of the Pell sequence are:
0, 1, 2, 5, 12, 29, 70, 169, 408, 985, 2378, 5741, 13860, 33461, 80782, 
Initiator: Child process 1596955 returned 142.
Initiator[1596951] : Forked process with ID 1596956.
Initiator[1596951]: Waiting for Process [1596956].
Composite[1596956]: First 15 composite numbers are:
4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 
Initiator: Child process 1596956 returned 25.
Initiator[1596951] : Forked process with ID 1596957.
Initiator[1596951]: Waiting for Process [1596957].
Total[1596957] : Sum = 120
Initiator: Child process 1596957 returned 120.
Pell: 142
Composite: 25
total: 120

Descriptions:
Pell.c: contains a method that returns the nth value of the pell sequence and an int main that calls it
Composite.c: contains a method that returns the nth composite number and an int main that calls it
Total.c: contains a method that returns the sum of 1->n and an int main that calls it
Initiator.c: contains a function that runs any single process and an int main that calls the function on all three other programs
Makefile: make build or make creates Pell, Composite, Total, and Initiator executables. Make clean removes all four executables. make package packages the code.
README.txt: answers questions, provides example output and descriptions of each file

Questions:
1. On success, it returns 0 to the child process, and returns the process id of the child process to the parent process. On failure, -1 is returned to the parent process and no child is created.
2. If the system lacks, the necessary resources to create a child process, fork() will fail.
3. WEXITSTATUS returns the least significant 8 bits of the status.
4. <sys/wait.h>
5. We are doing sequential processing because only one child is being ran at a time.
6. Yes. The output is line buffered.
