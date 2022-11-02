#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    //complain if not enough arguments have been given
    if(argc < 2){printf("Total[%d] : Too few arguments given!\n", getpid());exit(1);}
	
    //Set up shared memory
    char *total_name = argv[1];
	int total_fd = shm_open(total_name, O_CREAT | O_RDWR, 0666);
	int TOTAL_SIZE = 32;
	void* total_ptr = mmap(0, TOTAL_SIZE, PROT_WRITE, MAP_SHARED, total_fd, 0);
    
    //run program
    int n = atoi(argv[2]);//convert argument to integer
    sprintf(total_ptr, "%d", get_total(n));//copy result to shared memory pointer
    
	return 0;
}
