#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

//takes in index n and returns nth prime number
int get_prime(const int n)
{
    int results[n];//holds list of calculated prime numbers
    int index = 0;//current index of prime number being calculated
    int j = 2;//prime number that is supposed to be prime
    int i;//all values beneath number that is supposed to be prime

    //run loop until the number of prime values calculated is = to n
    while(index < n)
    {
        //check if j is a prime number
        for(i = 2; i < j; i++)
        {
            //divide j by every number less than j and check for remainder
            if(j%i == 0){break;}
        }
        //if no values of i divide j evenly,
        if(i==j)
        {
            //j is a prime number, so add it to the list
            results[index] = j;
            index++;
        }
        //increment j so that we check if the next value is a prime number
        j++;
    }
    j--;//counteract unnecessary j++ from loop
    //print out results
    printf("Prime[%d] : First %d prime numbers are:\n", getpid(), n);
    for(int i = 0; i < n; i++)
    {
        printf("%d, ", results[i]);
    }
    printf("\n");
    fflush(stdout);//ensure output is in order when printed to a file
    
    //return nth prime number
    return j;//or result[j-1]
}

int main(int argc, char *argv[])
{
    //complain if not enough arguments have been given
    if(argc < 2){printf("Prime[%d] : Too few arguments given!\n", getpid());exit(1);}
    
    //Set up shared memory
    char *prime_name = argv[1];
	int prime_fd = shm_open(prime_name, O_CREAT | O_RDWR, 0666);
	int PRIME_SIZE = 32;
	void* prime_ptr = mmap(0, PRIME_SIZE, PROT_WRITE, MAP_SHARED, prime_fd, 0);
    
    //run program
    int n = atoi(argv[2]);//convert argument to integer
    sprintf(prime_ptr, "%d", get_prime(n));//copy result to shared memory pointer
    
    return 0;
}