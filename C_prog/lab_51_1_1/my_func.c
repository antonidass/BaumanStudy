#include "my_func.h"

void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int find_maximums(FILE *input_stream, int *first_max_number, int *second_max_number)
{
    int number, rc = fscanf(input_stream, "%d%d", first_max_number, second_max_number);

    if (second_max_number > first_max_number)
        swap(first_max_number, second_max_number);

    if (rc != 2)
        return WRONG_DATA_ERR;

    while (1)
    {
        rc = fscanf(input_stream, "%d", &number);

        if (rc == EOF)
            return OK;

        if (rc != 1)
            return WRONG_DATA_ERR;

        if (number > *first_max_number)
        {
            *second_max_number = *first_max_number;
            *first_max_number = number;
        }
        else if (number > *second_max_number)
            *second_max_number = number;
    }
    return OK;
}