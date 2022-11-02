#include "Shared.h"

//opens file fileName, error checks, and returns a pointer to the opened file
FILE *openFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("%s couldn't be opened!\n", fileName);
        exit(1);
    }
    return fp;
}

//sums the numbers in file *fp
int calcTotal(FILE *fp)
{
    char str[10];
    int total = 0;
    while (fgets(str, 10, fp))
    {
        total += atoi(str);
    }
    return total;
}

int main(int argc, char *argv[])
{
    limitArgs(argc, argv, 3);

    FILE *fp = openFile(argv[1]);

    int total = calcTotal(fp);

    fclose(fp);

    int writePipe = atoi(argv[2]);
    write(writePipe, &total, sizeof(int));
}