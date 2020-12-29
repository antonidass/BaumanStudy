#include <stdio.h>

#define WRONG_MATRIX_LENGTH_ERROR 1
#define WRONG_MATRIX_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define N 10
#define M 10


void swap_rows(int *p_first, int *p_second, const int column)
{
    int t;
    int *p_first_root = p_first;
    
    while (p_first < p_first_root + column)
    {
        t = *p_first;
        *p_first = *p_second;
        *p_second = t;

        p_second++;
        p_first++;
    }
}

int read_matrix(int matrix[][M], const int row, const int column)
{
    int rc;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            rc = scanf("%d", &matrix[i][j]);
            if (rc != 1)
                return WRONG_MATRIX_ELEMENTS_ERROR;
        }
    }

    return OK;
}


void print_matrix(int matrix[][M], const int row, const int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}

int find_mult_row(int matrix[][M], const int row, const int column)
{
    int mult = 1;
    
    for (int j = 0; j < column; j++)
    {
        mult *= matrix[row][j];
    }

    return mult;    
}

void sort_rows(int matrix[][N], const int row, const int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < row - 1; k++)
        {
            if (find_mult_row(matrix, k, column) > find_mult_row(matrix, k + 1, column))
                swap_rows(matrix[k], matrix[k + 1], column);
        }
    }
}


int main()
{
    int matrix[N][M];
    int row, column;
    int res;

    printf("Enter the size of the matrix ");
    res = scanf("%d%d", &row, &column);

    if (res != 2 || row > MAX_SIZE || row < MIN_SIZE || column > MAX_SIZE || column < MIN_SIZE)
    {
        printf("Wrong matrix length");
        return WRONG_MATRIX_LENGTH_ERROR;
    }

    res = read_matrix(matrix, row, column);

    if (WRONG_MATRIX_ELEMENTS_ERROR == res)
    {
        printf("Wrong input data");
        return WRONG_MATRIX_ELEMENTS_ERROR;
    }

    sort_rows(matrix, row, column);

    print_matrix(matrix, row, column);

    return OK;
}