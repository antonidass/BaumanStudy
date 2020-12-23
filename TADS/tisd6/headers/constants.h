#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include "time.h"

#ifndef CONSTANTS

#define CONSTANTS


#define OK 0
#define MAX_LEN_LINE 100
#define SPACING 5

#define OK 0
#define FILE_ERROR 1
#define VAL_ERROR 2
#define STR_SIZE 128
#define FOUND 1
#define NOT_FOUND -10

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

    
#define ERROR_IN_INPUT_DATA -1
#define ERROR_IN_MALLOC -2
#define NOT_EXIST_ERROR -3
#define ERROR_IN_TABLE_SIZE -5


#define ERROR_IN_INPUT_DATA_MSG "Ошибка. Попытка ввести неккоректные данные! Строка номер: %d\n"
#define ERROR_IN_CHOICE_COMMAND_MSG "Ошибка. Некорректный ввод команды!\n"

#endif