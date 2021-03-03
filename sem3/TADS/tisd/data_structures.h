#pragma once
#include "constants.h"

typedef struct 
{
    int sign_of_mantissa;
    int field_of_mantissa[MAX_MANTISSA + 1];
    int mantissa_len;
    int sign_of_order;
    int order;
} float_num_t;

typedef struct 
{
  int sign_of_num;
  int number[MAX_MANTISSA];
  int number_len;
} int_num_t;

struct auxiliary_array_t
{
    int field[MAX_FIELD];
    int len;
};
