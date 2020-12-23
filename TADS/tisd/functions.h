#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_structures.h"




void main_division(float_num_t *divisible, int_num_t *divisor);
void secondary_div(struct auxiliary_array_t *divisible, int_num_t *divisor, int *multiplier);
int find_multiplier(struct auxiliary_array_t *divisible, int_num_t *divisor);
void subtraction(int num1[], int *n1, int num2[], int n2);
int zero_check(int *array, int length);
int array_cmp(int *array1, int length1, int *array2, int length2);
void multiply(int array[], int *n, int x);
void eliminate_last_nils_for_num(int_num_t *num);
void eliminate_last_nils(float_num_t *num);
void eliminate_lead_nils(int array[], int *n);
int count_lead_nils(int number_array[], int n);
void round_mantissa(float_num_t *num, int new_len);
void shift_left(int array[], int n);
void shift_right(int array[], int n);
void array_copy(int source_array[], int source_length, int target_array[]);
void choice_sign(int *first, int second);