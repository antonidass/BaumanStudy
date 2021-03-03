#include "../headers/iostream.h"
#include "../headers/functions.h"



int input_size(int *m, int *n)
{
    int rc = scanf("%d%d", m, n);

    if (rc != 2 || *m <= 0 || *n <= 0)
    {
        LOG_DEBUG("*m = %d  *n = %d", *m, *n);
        return ERROR_IN_INPUT_SIZE;
    }
    return OK;
}


void print_matrix(matrix_t matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int input_elems(matrix_t matrix, int m, int n)
{
    int rc;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            rc = scanf("%d", &matrix[i][j]);

            if (rc != 1)
                return ERROR_IN_INPUT_DATA;
        }

    return OK;
}


int input_matrix(matrix_t *matrix, int *m, int *n)
{
    int res = input_size(m, n);

    if (res == ERROR_IN_INPUT_SIZE)
        return res;
    
    *matrix = allocate_matrix(*m, *n);

    if (*matrix == NULL)
        return ERROR_IN_MATRIX_ALLOC;

    res = input_elems(*matrix, *m, *n);
    
    if (res == ERROR_IN_INPUT_DATA)
    {
        free_matrix(*matrix, *m);
        return ERROR_IN_INPUT_DATA;
    }

    return OK;
}


int input_power()
{
    int x;
    int rc = scanf("%d", &x);

    if (rc != 1 || x < 0)
        return ERROR_IN_INPUT_POWER;
    
    return x;
}