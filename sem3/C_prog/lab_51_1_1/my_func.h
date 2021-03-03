#include <stdio.h>

#define OK 0
#define WRONG_DATA_ERR -2

#define WRONG_DATA_MSG "Wrong input data"

int find_maximums(FILE *input_stream, int *first_max_number, int *second_max_number);
void swap(int *a, int *b);