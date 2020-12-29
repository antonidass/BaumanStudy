#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LOG_LEVEL 0
#include "macrologger.h"
#include "constants.h"


int input_size(int *m, int *n);
void print_matrix(matrix_t matrix, int m, int n);
int input_elems(matrix_t matrix, int m, int n);
int input_matrix(matrix_t *matrix, int *m, int *n);
int print_error(int error, FILE *stream);
int input_power();
