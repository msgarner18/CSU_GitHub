#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Executor.h"

//constrained values for random number of iterations
int get_iteration_no(int rand)
{
	return ((rand % (100 - 50) + 50));
}

//constrained values for random length of array
int get_arr_size(int rand)
{
	return ((rand % (150 - 100) + 100));
}

//constrained values for 1 random character produced
char get_arr_val(int rand)
{
	char number = ((rand % (91 - 65) + 65));
	return number;
}

//arr->array to be analyzed
//size->size of array to be analyzed
//maxCountPointer-> pointer to maxCount value to be adjusted
//output-> a floating point value that represents the ratio 
//of vowels over consonants and an adjusted maxCount if # of
//vowels counted is greater than any previous array
float ratio(char *arr, int size, int *maxCountPointer)
{
	int cCount = 0;
	int vCount = 0;
	char vowels[] = "AEIOU";
	bool isV = false;
	//printString(arr, size);

	for(int i = 0; i < size; i++)
	{
		isV = false;
		for(int j = 0; j < 5; j++)
		{
			//printf("arr[i] = %c, vowels[j] = %c\n", arr[i], vowels[j]);
			if(arr[i] == vowels[j])
			{
				
				isV = true;
			}
		}
		if(isV){vCount ++;}
		else{cCount++;}
	}
	
	if(*maxCountPointer < vCount)
	{
		*maxCountPointer = vCount;
	}
	//printf("vCount = %d, cCount = %d\n", vCount, cCount);
	return (float)vCount/cCount;
}

//uses above functions in order to produce a running ratio.
double get_running_ratio()
{
	int maxCount = 0;
	int maxIteration = 0;
	double ratioSum = 0;
	const int ITERNUM = get_iteration_no(rand());
	printf("[Executer.c]: Number of iterations is: %d\n", ITERNUM);
	for(int i = 0; i < ITERNUM; i++)
	{
		const int LENGTH = get_arr_size(rand());
		char *arr = malloc(sizeof(char)*LENGTH);
		for(int j = 0; j < LENGTH; j++)
		{
			arr[j] = get_arr_val(rand());
		}
		int tempCount = maxCount;
		int* mcPointer = &maxCount;
		ratioSum += ratio(arr, LENGTH, mcPointer);

		if(tempCount != maxCount)
		{
			maxIteration = i+1;
		}
		free(arr);
		arr = NULL;
	}
	printf("[Executor]: Iteration with maximum vowel count is: %d\n", maxIteration);
	ratioSum /= ITERNUM;
	return ratioSum;
}