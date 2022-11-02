#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
    //Ensure at least 1 argument was given to this program
    if(argc < 1){printf("Fibb[%d] : you must supply an argument!\n", getpid()); exit(1);}
	//convert argument to integer
    int n = atoi(argv[1]);
    
    //return nth element of fibonacci sequence
    return get_fib(n);
}

