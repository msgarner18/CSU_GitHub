#include "Shared.h"

//takes in index n and returns the sum of all integers from 0 to n
int get_total(const int n)
{
    int total = 0;

    //start at one and add to total until n is reached
    for (int i = 1; i <= n; i++)
    {
        total += i;
    }

    //print out results
    printf("Total[%d] : Sum = %d\n", getpid(), total);
    fflush(stdout); //ensure output is in order when printed to a file

    //return sum of first n numbers
    return total;
}

int main(int argc, char *argv[])
{
    limitArgs(argc, argv, 3);

    //convert argument to integer
    int n = atoi(argv[2]);

    //setup shared pointers
    char *name = argv[1];
    void *ptr = createSharedPtr(argv, name, 'w');

    //copy sum of first n numbers to shared memory pointer
    sprintf(ptr, "%d", get_total(n));

    return 0;
}
