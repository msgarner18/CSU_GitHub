#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int readNums(FILE * fp)
{
    char input[10];
    int total = 0;
    while(!feof(fp))
	{
		fscanf(fp, "%s", input);
        total+=atoi(input);
    }
    return total;
}

int main(int argc, char *argv[])
{
    //Ensure at least 1 argument was given to this program
    if(argc < 1){printf("CharacterReader[%d] : you must supply an argument!\n", getpid()); exit(1);}
	//convert argument to integer
    char* fileName;
	fileName = argv[1];
	FILE * fp= fopen(fileName, "r");
	//complain if file can't be opened
	if(!(fp = fopen(fileName, "r"))){printf("%s couldn't be opened!\n", fileName);exit(1);}
    int result = readNums(fp);
    fclose(fp);
	
    int writePipe = atoi(argv[2]);
    //write result to the write end of the pipe
    write(writePipe, &result, sizeof(int));

    return 0;
}