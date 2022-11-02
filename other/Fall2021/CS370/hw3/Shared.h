#ifndef SHARED_H_INCLUDED
#define SHARED_H_INCLUDED

//headers that I want in all of my programs
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

//creates a pipe and complains if it doesn't work
void createPipe(int fd[2])
{
    if (pipe(fd) == -1)
    {
        printf("Initiator[%d]: Pipe failed.\n", getpid());
        exit(1);
    }
}

//returns a shared pointer
//name is name of shared pointer
//rdwr is 'r' for read and 'w' for write
void *createSharedPtr(char *argv[], char name[], char rdwr)
{
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    int SIZE = 32;
    ftruncate(fd, SIZE);

    if (rdwr == 'r')
    {
        printf("%s[%d]: Created Shared memory \"%s\" with FD: %d\n", argv[0] + 2, getpid(), name, fd);
        return mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    }
    if (rdwr == 'w')
        return mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Shared[%d] : rdwr argument in createSharedPtr must be 'r' or 'w'!\n", getpid());
    exit(1);
}

//complains if number of arguments given are not equal to num
void limitArgs(int argc, char *argv[], int num)
{
    //ensure that at exactly 1 argument is given
    if (argc != num)
    {
        printf("%s[%d] : you must supply exactly %d argument(s)!\n", argv[0] + 2, getpid(), num - 1);
        exit(1);
    }
}

#endif