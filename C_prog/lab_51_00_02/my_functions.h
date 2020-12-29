#include <stdio.h>
#include <math.h>

#define WRONG_INPUT_DATA_ERR -2
#define NO_DATA_ERR -3
#define EPS = 1e-5
#define OK 0
#define LAUNCH_PARAMETERS_ERR -1
#define NO_FILE_ERR -4

#define LAUNCH_PARAMS_MSG "Error in launch params"
#define FILE_NAME_MSG "Error in file name"
#define NO_DATA_MSG "No data in file"
#define WRONG_INPUT_DATA_MSG "Wrong data in file"


double find_average(FILE *file);
double find_closest_to_average_number(FILE *file, double average);