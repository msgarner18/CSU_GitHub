#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"

int main(int argc, char *argv[])
{
    //assign seed to first argument and print it
    if (argc < 2)
    {
        printf("[Initiator]: must supply a seed!\n");
        exit(1);
    }
    int seed;
    seed = atoi(argv[1]);
    printf("[Initiator]: With seed: %d\n", seed);

    //set seed in randomizer
    srand(seed);

    //Invoke the Worker
    float running_ratio = get_running_ratio();

    //print running_ratio
    printf("[Initiator]: running ratio: %f\n", running_ratio);
}