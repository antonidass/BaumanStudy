#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>

#include "constants.h"
#include "data_structures.h"



void print_command_info();
void print_matrix(matrix_t matrix);
int read_matrix_from_file(matrix_t *matrix, FILE *file);
int *allocate_matrix(int m, int n);
int input_matrix_from_console(matrix_t *matrix);
int input_vector_from_console(matrix_t *vector);

void print_sparse_vector(sparse_vector_t sparse_vector);
void print_sparse_matrix(sparse_matrix_t sparse_matrix);

int read_vector_from_file(matrix_t *vector, FILE *file);
void print_sparse_mult_info(sparse_vector_t svector);
void print_all(matrix_t matrix, matrix_t vector, sparse_vector_t svector);
void print_elapsed_times(double elapsed_times[]);
void print_size();
int read_matrix_from_console(matrix_t *matrix, int not_null_count);