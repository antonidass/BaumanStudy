#include "my_functions.h"

double find_closest_to_average_number(FILE *file, double average)
{
    double number, closest_to_average_number, min_diff;
    int rc;

    fscanf(file, "%lf", &number);

    min_diff = fabs(number - average);
    closest_to_average_number = number;

    while (1)
    {
        rc = fscanf(file, "%lf", &number);

        if (rc == EOF)
            return closest_to_average_number;

        if (fabs(average - number) <= min_diff)
        {       
            min_diff = fabs(average - number);
            closest_to_average_number = number;
        }
    }
}

double find_average(FILE *file)
{
    double number, average = 0;
    int rc, count = 0;

    while (1)
    {
        rc = fscanf(file, "%lf", &number);

        if (rc == EOF && count == 0)
            return NO_DATA_ERR;

        if (rc == EOF)
            return average /= count;
        
        if (rc != 1)
            return WRONG_INPUT_DATA_ERR;
        
        average += number;
        count++;
    }
}