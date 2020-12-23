#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>


#ifndef CONSTANTS
#define CONSTANTS

#define MAX_AMOUNT_ELEMS_IN_QUEUE 100
#define OK 0
#define ERROR_IN_CHOICE_COMMAND -1
#define QUEUE_OVERFLOW -2
#define EMPTY_QUEUE -5
#define EMPTY 1
#define NOT_EMPTY 0
#define FRONT_OVERFLOW -3
#define END_OVERFLOW -4
#define ERROR_IN_AMOUNT_TASKS -5
#define ERROR_IN_AMOUNT_ELEMS -6
#define NO_ELEMENTS -10


#define TASKS_AMOUNT 100
#define PROBABILITY 70
#define FIRST_SERVICE_IN 0
#define FIRST_SERVICE_OUT 6
#define SECOND_SERVICE_IN 1
#define SECOND_SERVICE_OUT 8
#define MAX_TASKS 1000
#define MID_TASKS 100

#endif



#ifndef MSGES
#define MSGES

#define ERROR_IN_CHOICE_COMMAND_MSG "Введена неверная команда!\n"


#endif