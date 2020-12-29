#include "../headers/functions.h"



void free_matrix(matrix_t matrix, int m)
{
    for (int i = 0; i < m; i++)
    {
        if (matrix[i])
            free(matrix[i]);
    }
    free(matrix);
}


matrix_t allocate_matrix(int m, int n)
{
    matrix_t data = malloc(m * sizeof(row_t));
    LOG_DEBUG("!!!! Main malloc !!!! %d ", m);

    if (!data) 
        return NULL;
    
    for (int i = 0; i < m; i++)
    {
        data[i] = malloc(n * sizeof(int));
        LOG_DEBUG(" !! Second malloc !!  %d ", i);

        if (!data[i])
        {
            free_matrix(data, m);
            return NULL;
        }
    }

    return data;
}


matrix_t reallocate_matrix(matrix_t matrix, int m, int addition_size)
{
    matrix = realloc(matrix, (m + addition_size) * sizeof(row_t));
    LOG_DEBUG("   !!!! Realloc !!!!!  basic = %d    add = %d", m, addition_size);

    for (int i = 0; i < m + addition_size; i++)
    {
        LOG_DEBUG(" ! Third malloc ! %d %d ", m, i);

        if (i < m)
            matrix[i] = realloc(matrix[i], sizeof(int) * (m + addition_size));
        else
            matrix[i] = malloc((m + addition_size) * sizeof(int));

        if (!matrix[i])
        {
            free_matrix(matrix, m + i);
            return NULL;
        }
    }

    return matrix;
}


void find_index_max_elem_in_matrix(matrix_t matrix, int m, int n, int *i_max, int *j_max)
{
    int max_elem = matrix[0][0];
    *i_max = *j_max = 0;

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (matrix[i][j] > max_elem)
            {
                max_elem = matrix[i][j];
                *i_max = i;
                *j_max = j;
            }
            // LOG_DEBUG("matrix[j][i] = %d", matrix[i][j]);
        }
    }
}


void shift_left(matrix_t matrix, int row, int column, int begin)
{
    for (int i = begin; i < column - 1; i++)
        matrix[row][i] = matrix[row][i + 1];
}


void copy_row_elements(row_t dst, row_t src, int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i]; 
}


void free_deleted_element(matrix_t matrix, int m, int n)
{
    row_t row;

    for (int i = 0; i < m; i++)
    {
        row = malloc((n - 1) * sizeof(int));
        copy_row_elements(row, matrix[i], n - 1);
        free(matrix[i]);
        matrix[i] = row;
    }
}


void delete_column(matrix_t matrix, int m, int n, int j_deletable)
{
    for (int i = 0; i < m; i++)
        shift_left(matrix, i, n, j_deletable);

    free_deleted_element(matrix, m, n);
}


void delete_row(matrix_t matrix, int m, int i_deletable)
{
    free(matrix[i_deletable]);
    for (int i = i_deletable; i < m - 1; i++)
    {
        matrix[i] = matrix[i + 1];
        // LOG_DEBUG("i = %d   m = %d   ", i, m);
    }
}


void cut_matrix(matrix_t matrix, int *m, int *n)
{
    int i_max, j_max;

    if (*m < *n)
    {
        while (*m != *n)
        {
            find_index_max_elem_in_matrix(matrix, *m, *n, &i_max, &j_max);
            // LOG_DEBUG("max_elem_index = ( %d,  %d) ", i_max, j_max);
            delete_column(matrix, *m, *n, j_max);
            (*n)--;
        }

        return;
    }

    while (*m != *n)
    {
        find_index_max_elem_in_matrix(matrix, *m, *n, &i_max, &j_max);
        // LOG_DEBUG("max_elem_index = ( %d,  %d) ", i_max, j_max);
        delete_row(matrix, *m, i_max);
        (*m)--;
    }
}


int print_error(int error, FILE *stream)
{
    if (error == ERROR_IN_INPUT_SIZE)
    {
        fprintf(stream, ERROR_IN_INPUT_SIZE_MSG);
        return error;
    }

    if (error == ERROR_IN_INPUT_DATA)
    {
        fprintf(stream, ERROR_IN_INPUT_DATA_MSG);
        return error;
    }

    if (error == ERROR_IN_MATRIX_ALLOC)
    {
        fprintf(stream, ERROR_IN_MATRIX_ALLOC_MSG);
        return error;
    }

    return OK;
}


int find_average(matrix_t matrix, int row, int column)
{
    double average = 0;

    for (int i = 0; i < row; i++)
        average += matrix[i][column];
    
    // LOG_DEBUG("Average = %d", average / row);

    return (int)floor(average / (double) row);
}


int find_max_in_row(matrix_t matrix, int row, int column)
{
    int max_elem = matrix[row][0];

    for (int i = 1; i < column; i++)
        if (matrix[row][i] > max_elem)
            max_elem = matrix[row][i];

    return max_elem;
}


void addition_matrix(matrix_t matrix, int m, int addition_size)
{
    for (int i = m; i < addition_size; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = find_average(matrix, i, j);
        }
    }

    for (int i = 0; i < addition_size; i++)
    {
        for (int j = m; j < addition_size; j++)
        {
            matrix[i][j] = find_max_in_row(matrix, i, j);
        }
    }
}


int mult_row_by_column(matrix_t matrix_first, int m, matrix_t matrix_second, int row, int column)
{
    int res = 0;
    for (int i = 0; i < m; i++)
    {
        // LOG_DEBUG("matrix_first = %d, matrix_second = %d    Mult =  %d ", matrix_first[row][i], matrix_second[i][column], matrix_first[row][i] * matrix_second[i][column]);
        res += matrix_first[row][i] * matrix_second[i][column];
    }
    // LOG_DEBUG("Result of mult row by column = %d", res);
    return res;
}


void make_identity_matrix(int size, matrix_t matrix)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }
}


void copy_matrix(matrix_t dst, matrix_t src, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dst[i][j] = src[i][j];
}


void mult_matrix(matrix_t matrix_first, matrix_t matrix_second, int matrix_size, matrix_t res_matrix)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            res_matrix[i][j] = mult_row_by_column(matrix_first, matrix_size, matrix_second, i, j);
        }   
    }
}


void power_matrix(matrix_t matrix, int size, int power, matrix_t *res_matrix)
{
    if (power == 0)
    {
        make_identity_matrix(size, *res_matrix);
        return;
    }

    if (power == 1)
    {
        copy_matrix(*res_matrix, matrix, size);
        return;
    }

    matrix_t temp_matrix = allocate_matrix(size, size);
    copy_matrix(temp_matrix, matrix, size);

    for (int i = 1; i < power; i++)
    {   
        mult_matrix(temp_matrix, matrix, size, *res_matrix);
        copy_matrix(temp_matrix, *res_matrix, size);
    }

    free_matrix(temp_matrix, size);
}