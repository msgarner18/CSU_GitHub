//This file contains all #includes and functions that I want access to in all of my code
#include "Shared.h"

//runs the Reader.c code with the argument supplied and returns what Reader.c returns
//Reader.c takes a file as an argument and returns the sum of all numbers in that file
int runReader(char *arg)
{
    int total;
    int fd[2]; //fd[0]-read, fd[1]-write
    createPipe(fd);

    int id = fork();
    if (id == 0)
    {
        char arr[16];              //This is to store the pipe reference as a string
        sprintf(arr, "%d", fd[1]); //puts adrres of write pipe inside of arr
        char *prog = "./Reader";
        execlp(prog, prog, arg, arr, NULL);
    }
    else
    {
        close(fd[1]);
        read(fd[0], &total, sizeof(int));
        close(fd[0]);
        printf("Inititator[%d]: contents read from the read end pipe: %d\n", getpid(), total);
    }
    return total;
}

int main(int argc, char *argv[])
{
    //get sum of all values in inputFile
    char *inputFile = argv[1];
    int total = runReader(inputFile);
    char ctotal[10];
    sprintf(ctotal, "%d", total);

    //pell's shared memory segment (print name and file descriptor)
    char *pell_name = "SHM_Pell";
    void *pell_ptr = createSharedPtr(argv, pell_name, 'r');

    //composite's shared memory segment (print name and file descriptor)
    char *composite_name = "SHM_Composite";
    void *composite_ptr = createSharedPtr(argv, composite_name, 'r');

    //total's shared memory segment (print name and file descriptor)
    char *total_name = "SHM_Total";
    void *total_ptr = createSharedPtr(argv, total_name, 'r');

    //fork 3 processes
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    if (pid1 == 0 && pid2 != 0) //Pell
    {
        char *prog = "./Pell";
        execlp(prog, prog, pell_name, ctotal, NULL);
    }
    if (pid1 != 0 && pid2 == 0) //Composite
    {
        char *prog = "./Composite";
        execlp(prog, prog, composite_name, ctotal, NULL);
    }
    if (pid1 == 0 && pid2 == 0) //Total
    {
        char *prog = "./Total";
        execlp(prog, prog, total_name, ctotal, NULL);
    }
    if (pid1 != 0 && pid2 != 0) //parent
    {
        wait(NULL);
        wait(NULL);
        wait(NULL);
        int pell_counter = atoi(pell_ptr);
        int composite_counter = atoi(composite_ptr);
        int total_counter = atoi(total_ptr);

        //unlink shared memory pointers
        shm_unlink(pell_name);
        shm_unlink(composite_name);
        shm_unlink(total_name);

        printf("%s[%d]: Pell last number: %d\n", argv[0] + 2, getpid(), pell_counter);
        printf("%s[%d]: Composite last number: %d\n", argv[0] + 2, getpid(), composite_counter);
        printf("%s[%d]: Total last number: %d\n", argv[0] + 2, getpid(), total_counter);
    }
}
