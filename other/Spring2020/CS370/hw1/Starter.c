#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

int main(int argc, char *argv[])
{
	//assign seed to first argument and print it
	if(argc < 2){printf("[Starter.c]: must supply a seed!\n");exit(1);}
	int seed;
	seed = atoi(argv[1]);
	printf("[Starter.c]: With seed: %d\n", seed);

	//set seed in randomizer
	srand(seed);
	
	//run running ratio and print it out
	double running_ratio = get_running_ratio();
	printf("[Starter]: Running ratio: %f\n", running_ratio);
	
}
