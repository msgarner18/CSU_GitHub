#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Worker.h"

// returns a random integer value between lower_bound (inclusive) and upper_bound (exclusive)
int random_in_range(int lower_bound, int upper_bound)
{
    return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}

// Returns number of elements in array that are divisible by divisor
int get_divisibility_count(int *array, int arraySize, int divisor)
{
    int total = 0;

    //go through each element in array
    for (int i = 0; i < arraySize; i++)
    {
        //for each element that is divisible by the divisor, add 1 to total
        if (array[i] % divisor == 0)
        {
            total += 1;
        }
    }

    return total;
}

//return the running ratio as dictated by the assignment
float get_running_ratio()
{
    //initialize values
    int maxDivisibleElements = 0;
    int maxCountIteration = 0;
    float ratioSum = 0;
    int totalIterations = random_in_range(50, 100);
    printf("[Worker]: Number of iterations is: %d\n", totalIterations);

    //create totalIterations number of arrays and fill them with a random ammount of random values
    for (int i = 0; i < totalIterations; i++)
    {
        //Fill array with LENGTH number of random values
        const int LENGTH = random_in_range(100, 150);
        int *array = malloc(sizeof(int) * LENGTH);
        for (int i = 0; i < LENGTH; i++)
        {
            array[i] = random_in_range(1, 100);
        }

        //calculate number of elements in array that are divisible by random divisor
        int divisor = random_in_range(5, 15);
        int count = get_divisibility_count(array, LENGTH, divisor);

        //add ratio to ratioSum to be used at the end
        ratioSum += count / (float)(LENGTH - count);

        //Keep track of which array iteration contained the max number of divisible elements
        if (count > maxDivisibleElements)
        {
            maxDivisibleElements = count;
            maxCountIteration = i + 1;
        }

        //If you comment out this line, you will produce a memory leak
        free(array);
    }

    printf("[Worker]: Iteration with maximum fully divisible elements is %d\n", maxCountIteration);
    return ratioSum / totalIterations;
}
