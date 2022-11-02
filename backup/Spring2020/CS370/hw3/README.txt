Starter.c- forks all the children and starts the exececution of all the other files
CharacterReader.c- reads all the lines and will keep a running sum of the lines and return the result to the write end of the pipe.
Fibb.c- returns the nth value in fibonacci sequence as passed by Starter.c.
Prime.c- returns the nth prime number as passed by Starter.c
Total.c- returns the sum of all number from zero to n as passed by Starter.c.

Questions:
1) pipe() creates a pipe and the fd[0] reads and the fd[1] end writes
2) mmap()
3) shm_open() returns an integer