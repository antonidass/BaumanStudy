#pragma once
#include "constants.h"
#include "data_structures.h"



void table_info();
int int_input(char *integer_number, FILE *stream);
int float_input(char *float_number, FILE *stream);
int parse_int(char *int_num, int num_array[], int *sign_int);
int parse_float(char *float_num, float_num_t *num_t);
int print_answer(float_num_t num);