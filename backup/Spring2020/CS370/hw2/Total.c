#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

//takes in index n and returns the sum of all integers less than n and greater than 0. (n+n-1+...+0)
int get_total(const int n)
{
    int total = 0;//holds the value returned
    
    //start at one and add to total until n is reached
    for(int i = 1; i<=n; i++)
    {
        total+=i;
    }

    //print out results
    printf("Total[%d] : Sum = %d\n", getpid(), total);
    fflush(stdout);//ensure output is in order when printed to a file
    
    //return sum of first n numbers
    return total;
}

int main(int argc, char *argv[])
{
    //ensure that at least one argument is given
    if(argc < 1){printf("Total[%d] : you must supply an argument!\n", getpid());exit(1);}
	
    //convert argument to integer
    int n = atoi(argv[1]);

    //return sum of first n numbers
	return get_total(n);
}
