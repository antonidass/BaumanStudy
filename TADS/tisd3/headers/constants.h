#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#define YES 1
#define NO 0
#define OK 0
#define COUNT_REPEATS 10
#define ERROR_IN_CHOICE_COMMAND -1
#define ERROR_IN_SIZE_MATRIX -2
#define ERROR_IN_VECTOR_SIZE -3
#define ERROR_IN_INPUT_ELEMS -4
#define ERROR_IN_PERCENT -5
#define ERROR_IN_FORMAT -6
#define ERROR_IN_SIZE_MULT -7
#define MAX_POSSIBLE_TIME 10000000
#define REPEATS 28


#define ERROR_IN_CHOICE_COMMAND_MSG "Ошибка в выборе команды\n"
#define ERROR_IN_SIZE_MATRIX_MSG "Ошибка. Введен неверный размер матрицы.\n"
#define ERROR_IN_SIZE_MULT_MSG "Ошибка. Количество строк вектора должно равняться количеству столбцов матрицы\n"
