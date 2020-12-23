#include "iostream.h"

void common_mult(const matrix_t *matrix, const matrix_t *vector, matrix_t *res_matrix);
void parse_matrix(matrix_t matrix, sparse_matrix_t *sparse_matrix);
void parse_vector(matrix_t vector, sparse_vector_t *svector);
int main_menu(matrix_t *matrix, matrix_t *vector, matrix_t *res_matrix, sparse_matrix_t *smatrix, sparse_vector_t *svector, sparse_vector_t *sres);
int generate(matrix_t *matrix, matrix_t *vector);
int counting_time();
void sparse_mult(const sparse_matrix_t *smatrix, const sparse_vector_t *svector, sparse_vector_t *sres);
void free_all(matrix_t *matrix, matrix_t *vector, matrix_t *res_matrix, sparse_matrix_t *smatrix, sparse_vector_t *svector, sparse_vector_t *sres);