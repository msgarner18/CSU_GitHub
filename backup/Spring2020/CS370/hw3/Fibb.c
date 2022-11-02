#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

//takes in index n and returns nth element of fibonacci sequence where
int get_fib(const int n)
{
    int results[n];//holds list of values in fibonacci sequence
    int prev = 0;//previous value in fib suquence
    int cur = 1;//current value in fib suquenc
    //starts at 2 because the first two elements are given: 0, 1
    for(int i = 2; i < n; i++)
    {
        //calculate next value in sequence
        results[i] = cur+prev;
        //move prev and cur up to next value
        prev = cur;
        cur = results[i];
    }

    //don't calculate results 0 and 1 if n is too small-avoid segmentation fault
    if(n >= 1){results[0] = 0;}
    if(n >= 2){results[1] = 1;}

    //print out array in proper format
    printf("Fibb[%d] : Number of terms in fibonacii series is %d\n", getpid(), n);
    printf("Fibb[%d] : The first %d numbers of the Fibonacci sequence are:\n", getpid(), n);
    for(int i = 0; i < n; i++)
    {
        printf("%d, ", results[i]);
    }
    printf("\n");
    fflush(stdout);//ensure output is in order when printed to a file
    
    //return nth value in fibonacci sequence
    return results[n-1];
}

int main(int argc, char* argv[])
{
    //complain if not enough arguments have been given
    if(argc < 2){printf("Fibb[%d] : Too few arguments given!\n", getpid());exit(1);}
    //setup shared memory
    char *fib_name = argv[1];
    int fib_fd = shm_open(fib_name, O_CREAT | O_RDWR, 0666);
	int FIB_SIZE = 32;
	
	void* fib_ptr = mmap(0, FIB_SIZE, PROT_WRITE, MAP_SHARED, fib_fd, 0);

    //run program
    int n = atoi(argv[2]);//convert argument to integer
    sprintf(fib_ptr, "%d", get_fib(n));//copy result to shared memory pointer

    return 0;
}

