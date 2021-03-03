#include <stdio.h>

#define WRONG_MATRIX_LENGTH_ERROR 1
#define WRONG_MATRIX_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define N 10
#define M 10
#define SAME 0
#define VARIOUS 1

int various_signs_condition(const int first, const int second)
{
    if (first * second >= 0)
        return SAME;
    
    return VARIOUS;
}

void form_array(int matrix[][M], const int row, const int column, int *pa)
{
    for (int j = 0; j < column; j++)
    {   
        int count = 0;
        for (int i = 1; i < row; i++)
            count += various_signs_condition(matrix[i - 1][j], matrix[i][j]);
        
        *pa = (count == row - 1 && row > 1);
        pa++;
    }
}

void print_array(const int array[], const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
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

    int array[M];

    form_array(matrix, row, column, array);

    print_array(array, column);

    return OK;
}