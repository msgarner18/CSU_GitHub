#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

//this function takes in a program name and the first argument of the program
//it runs the program in proper fork() execlp() wait() order and returns the result of the program
int get_process(char *prog, char *str)
{
    int stat; //used as parameter in wait functions
    pid_t pid = fork();
    if (pid == 0) //child process
    {
        //execute program using str as an argument
        execlp(prog, prog, str, NULL);
    }
    else //parent process
    {
        printf("Initiator[%d] : Forked process with ID %d.\n", getpid(), pid);
        printf("Initiator[%d]: Waiting for Process [%d].\n", getpid(), pid);
        fflush(stdout); //ensure output is in order when printed to a file
        //wait for child process to finish
        wait(&stat);
        //check if return value was valid
        if (WIFEXITED(stat))
        {
            printf("Initiator: Child process %d returned %d.\n", pid, WEXITSTATUS(stat));
            fflush(stdout); //ensure output is in order when printed to a file
        }
        else
        {
            //if not valid, print error message and exit program
            printf("Program %s returned a non-zero value!", prog);
            exit(1);
        }
    }
    return WEXITSTATUS(stat); //return what prog returned
}

int main(int argc, char *argv[])
{
    //ensure that this program is run with exactly 1 argument.
    if (argc != 2)
    {
        printf("Initiator: must supply a text file!\n");
        exit(1);
    }

    //read argument into fp
    char *fileName;
    fileName = argv[1];
    FILE *fp = fopen(fileName, "r");
    //complain if file can't be opened
    if (!(fp = fopen(fileName, "r")))
    {
        printf("%s couldn't be opened!\n", fileName);
        exit(1);
    }

    //run until end of file is hit
    char str[10];   //input string
    int results[3]; //holds the values returned by the three programs
    while (!feof(fp))
    {
        fscanf(fp, "%s", str); //read first line from fp and return to str
        results[0] = get_process("./Pell", str);
        results[1] = get_process("./Composite", str);
        results[2] = get_process("./Total", str);

        //print results from running the 3 programs
        printf("Pell: %d\nComposite: %d\ntotal: %d\n", results[0], results[1], results[2]);
        fflush(stdout); //ensure output is in order when printed to a file
    }

    //close file fp
    fclose(fp);
    return 0;
}
