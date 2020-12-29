#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_LEVEL 0

#include "macrologger.h"
#include "constants.h"


int find_amount_of_elems(FILE *input_data);
int *read_data(FILE *input_data, int *pb_src);
void print_data(int *array, int amount);
void write_data(FILE *output_data, int *pb, int *pe);
