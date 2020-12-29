#include "my_functions.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(LAUNCH_PARAMS_MSG);
        return LAUNCH_PARAMETERS_ERR;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf(FILE_NAME_MSG);
        return NO_FILE_ERR;
    }

    double average = find_average(file);

    if (average == NO_DATA_ERR)
    {
        printf(NO_DATA_MSG);
        return NO_DATA_ERR;
    }
    
    if (average == WRONG_INPUT_DATA_ERR)
    {
        printf(WRONG_INPUT_DATA_MSG);
        return WRONG_INPUT_DATA_ERR;
    }

    rewind(file);

    double ans = find_closest_to_average_number(file, average);

    fclose(file);

    printf("%.5lf", ans);

    return OK;
}