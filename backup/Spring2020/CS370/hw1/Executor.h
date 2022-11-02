#ifndef EXECUTOR_H_INCLUDED
#define EXECUTOR_H_INCLUDED

int get_iteration_no(int rand);
int get_arr_size(int rand);
char get_arr_val(int rand);
float ratio(char *arr, int size, int *maxCountPointer);
double get_running_ratio();
#endif