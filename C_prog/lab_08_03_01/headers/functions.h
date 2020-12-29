#include "iostream.h"

void free_matrix(matrix_t data, int m);
matrix_t allocate_matrix(int m, int n);
void cut_matrix(matrix_t matrix, int *m, int *n);
void find_index_max_elem_in_matrix(matrix_t matrix, int m, int n, int *i_max, int *j_max);
void delete_column(matrix_t matrix, int m, int n, int j_deletable);
void shift_left(matrix_t matrix, int row, int column, int begin);
int find_average(matrix_t matrix, int row, int column);
void addition_matrix(matrix_t matrix, int m, int complement_size);
matrix_t reallocate_matrix(matrix_t matrix, int m, int addition_size);
int mult_row_by_column(matrix_t matrix_first, int m, matrix_t matrix_second, int row, int column);
void power_matrix(matrix_t matrix, int size, int power, matrix_t *res_matrix);
void delete_row(matrix_t matrix, int m, int i_deletable);
void mult_matrix(matrix_t matrix_first, matrix_t matrix_second, int matrix_size, matrix_t res_matrix);
void copy_matrix(matrix_t dst, matrix_t src, int size);
void free_deleted_element(matrix_t matrix, int m, int n);
void copy_row_elements(row_t dst, row_t src, int n);
void make_identity_matrix(int size, matrix_t matrix);