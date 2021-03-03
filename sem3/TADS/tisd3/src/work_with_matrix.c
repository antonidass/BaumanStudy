#include "../headers/functions.h"






void common_mult(const matrix_t *matrix, const matrix_t *vector, matrix_t *res_matrix)
{
    for (int i = 0; i < matrix->row; ++i)
    {
        res_matrix->matrix[i] = 0;
        for (int j = 0; j < matrix->column; ++j)
            res_matrix->matrix[i] += matrix->matrix[i * matrix->column + j] * vector->matrix[j]; 
    }
}


void parse_vector(matrix_t vector, sparse_vector_t *svector)
{
    int count_elems = 0;
    for (int i = 0; i < vector.row; i++)
        for (int j = 0; j < vector.column; j++)
            if (vector.matrix[i * vector.column + j] != 0)
                count_elems++;

    svector->not_null_elems_amount = count_elems;
    svector->all_elems_amount = vector.row;


    svector->values = malloc(sizeof(int) * count_elems);
    svector->indexes = calloc(vector.row, sizeof(int));

    int k = 0;
    for (int i = 0; i < vector.row; i++)
    {
        if (vector.matrix[i] != 0)
        {
            svector->values[k] = vector.matrix[i];
            svector->indexes[i] = k + 1;
            k++;
        }
    }
}

void parse_matrix(matrix_t matrix, sparse_matrix_t *smatrix)
{
    int count_elems = 0;
    for (int i = 0; i < matrix.row; i++)
        for (int j = 0; j < matrix.column; j++)
            if (matrix.matrix[i * matrix.column + j] != 0)
                count_elems++;

    smatrix->elems_amount = count_elems;

    smatrix->values = malloc(sizeof(int) * count_elems);
    smatrix->columns = malloc(sizeof(int) * count_elems);
    smatrix->pointers = calloc(matrix.row + 1, sizeof(int));

    int k = 0;
    int count_elements_in_row = 0;
    int pointer = 0;
    smatrix->pointers[pointer] = 0;

    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.column; j++)
        {
            if (matrix.matrix[i * matrix.column + j] != 0)
            {
                smatrix->values[k] = matrix.matrix[i * matrix.column + j];
                smatrix->columns[k++] = j;           
                count_elements_in_row++; 
            }
        }
        
        smatrix->pointers[++pointer] = count_elements_in_row;
    }   

    smatrix->row = pointer + 1;
}



void sparse_mult(const sparse_matrix_t *smatrix, const sparse_vector_t *svector, sparse_vector_t *sres)
{
    int count_not_nul = 0;
    int sres_i = 0;
    int sum = 0;

    for (int i = 0; i < smatrix->row - 1; i++)
    {
        sum = 0;
        for (int j = smatrix->pointers[i]; j < smatrix->pointers[i + 1]; j++)
            sum += smatrix->values[j] * svector->values[svector->indexes[smatrix->columns[j]] - 1];
        
        if (sum != 0)
        {
            sres->values[sres_i] = sum;
            sres->indexes[sres_i] = i + 1;
            sres_i++;
            count_not_nul++;
        }
    }

    sres->not_null_elems_amount = count_not_nul;   
}

