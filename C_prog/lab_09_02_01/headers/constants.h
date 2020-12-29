#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macrologger.h"


#ifndef CONSTANTS
#define CONSTANTS

#define OK 0
#define MAX_OBJECTS 15
#define EPS 1e-5
#define POSITIVE_NUMBER 1
#define NEGATIVE_NUMBER -1
#define ZERO 0

#define OBJECT_FIELD_AMOUNT 3
#define AMOUNT_PARAMS_ERR -1
#define FILE_NAME_ERR -2
#define DATA_ERR -3
#define LEN_WORD_ERR -4
#define ZERO_SUBSTRING_OBJECTS_ERR -6
#define ERROR_IN_READ -7
#define FILE_CLOSE_ERR -8
#define ERROR_IN_MALLOC -9
#define ERROR_IN_FIELD -10
#define EMPTY_FILE_ERROR -11




typedef struct object
{
    char *name;
    double mass;
    double volume;
    double density;
} object_t;

#endif




