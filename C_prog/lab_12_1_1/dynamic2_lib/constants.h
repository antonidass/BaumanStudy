#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macrologger.h"


#ifndef CONSTANTS
#define CONSTANTS

#define OK 0
#define YES 1
#define NO 0
#define MAX_FILE_NAME 100
#define ERROR_ARG_FILTER -12
#define ERROR_ARGS -1
#define ERROR_IN_INPUT_DATA -2
#define EMPTY_DATA_ERROR -3
#define ERROR_IN_MALLOC -5
#define ERROR_IN_OPEN_FILE -6
#define NO_DATA_ERROR -7
#define NO_ELEMENTS_BETWEEN_ERROR -8
#define ERROR_IN_CLOSING_FILE -9
#define ERROR_IN_PARAM_NAME -10
#define EMPTY_ARRAY_ERR -11

#define ERROR_ARGS_MSG "Error in amount of args\n"
#define ERROR_IN_INPUT_DATA_MSG "Error in input data\n"
#define EMPTY_DATA_ERROR_MSG "Empty data in file\n"
#define ERROR_IN_MALLOC_MSG "Error in memory allocation\n"
#define ERROR_IN_OPEN_FILE_MSG "Error in opening file\n"
#define NO_DATA_MSG "Error in filter function\n"
#define NO_ELEMENTS_BETWEEN_ERROR_MSG "No data between min and max elements after filter\n"
#define ERROR_IN_CLOSING_FILE_MSG "Error in file closing\n"
#define ERROR_IN_PARAM_NAME_MSG "Error in parameter's name\n"
#define EMPTY_ARRAY_ERR_MSG "Empty file when started filter\n"
#define ERROR_ARG_FILTER_MSG "Error name of filter\n"


typedef int (comp_function_t)(const void *, const void *);


typedef struct
{
    int *left;
    int *right;
} edges_t;

#endif