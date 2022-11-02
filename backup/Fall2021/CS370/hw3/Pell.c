#include "Shared.h"
#include <math.h>

//return nth value in pell sequence
int get_pell(const int n)
{
    double numerator = -pow(1 - sqrt(2), n - 1) + pow(1 + sqrt(2), n - 1);
    double denominator = 2 * sqrt(2);
    float returnVal = numerator / denominator;

    return returnVal;
}

//prints all pell values up to n
void print_pell(const int n)
{
    //print sequence of numbers in Pell sequence
    printf("Pell[%d]: Number of terms in Pell series is %d\n", getpid(), n);
    printf("Pell[%d]: The first %d numbers of the Pell sequence are:\n", getpid(), n);
    for (int i = 1; i <= n; i++)
    {
        printf("%d, ", get_pell(i));
    }
    printf("\n");
    fflush(stdout); //ensure output is in order when printed to a file
}

int main(int argc, char *argv[])
{
    limitArgs(argc, argv, 3);

    //convert argument to integer
    int n = atoi(argv[2]);

    //print necessary pell information
    print_pell(n);

    //setup shared memory
    char *name = argv[1];
    void *ptr = createSharedPtr(argv, name, 'w');

    //copy nth pell number to shared memory pointer
    sprintf(ptr, "%d", get_pell(n));

    return 0;
}