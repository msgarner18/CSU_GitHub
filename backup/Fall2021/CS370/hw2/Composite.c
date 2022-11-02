#include "Shared.h"

//returns the nth composite value and prints the sequence up to n
int get_composite(const int n)
{
    int results[n]; //holds list of prime numbers
    int length = 1; //number of elements results[n] contains
    results[0] = 4; //first element in results[n]
    int value = 5;  //first proposed value for next composite value

    //fill results[n] array from 1 -> n (0 is already full)
    for (int i = 1; i < n; i++)
    {
        //keep trying to find next composite value until one is found
        while (length <= i)
        {
            //test every possible divisor starting with 2 to see if current value being tested is composite
            int divisor = 2;
            while (divisor < value)
            {
                //if a composite value is found, add it to the list, and start looking for the next composite value
                if (value % divisor == 0)
                {
                    results[i] = value;
                    length += 1;
                    break;
                }
                divisor += 1;
            }
            value += 1;
        }
    }

    //print composite values
    printf("Composite[%d]: First %d composite numbers are:\n", getpid(), n);
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", results[i]);
    }
    printf("\n");
    fflush(stdout); //ensure output is in order when printed to a file

    //return the nth composite value (index 0 holds the first composite value)
    return results[n - 1];
}

int main(int argc, char *argv[])
{
    limitArgs(argc, argv, 3);

    //setup shared memory
    char *name = argv[1];
    void *ptr = createSharedPtr(argv, name, 'w');

    //convert argument to integer
    int n = atoi(argv[2]);

    //return nth pell number
    return get_composite(n);
}