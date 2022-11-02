#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
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
    //Ensure that exactly 1 argument is given to this program
    if (argc != 2)
    {
        printf("Pell[%d] : you must supply an argument!\n", getpid());
        exit(1);
    }
    //convert argument to integer
    int n = atoi(argv[1]);

    //print necessary pell information
    print_pell(n);

    //return nth pell number
    return get_pell(n);
}