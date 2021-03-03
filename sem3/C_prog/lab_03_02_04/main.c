#include <stdio.h>
#include <math.h>

#define WRONG_MATRIX_LENGTH_ERROR 1
#define WRONG_MATRIX_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define N 10
#define M 10
#define NO 0
#define YES 1
#define CANNOT_FIND_NUM -1
#define NOT_FOUND 0

int find_last_digit(int num)
{
    num = fabs(num);
    if (num % 10 == 5)
        return YES;

    return NO;
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

int find_element(int matrix[][M], const int row, const int column)
{
    int max_num = NOT_FOUND;

    for (int i = 1; i < row; i++)
    {
        for (int j = column - 1; j > column - i - 1; j--)
        {
            if (find_last_digit(matrix[i][j]) && (matrix[i][j] > max_num || !max_num))
                max_num = matrix[i][j];
        }
    }

    if (max_num)
        return max_num;
    
    return CANNOT_FIND_NUM;
}

int main()
{
    int matrix[N][M];
    int row, column;
    int res;

    printf("Enter the size of the matrix ");
    res = scanf("%d%d", &row, &column);

    if (res != 2 || row > MAX_SIZE || row < MIN_SIZE || column > MAX_SIZE || column < MIN_SIZE || row != column)
    {
        printf("Wrong matrix length");
        return WRONG_MATRIX_LENGTH_ERROR;
    }

    res = read_matrix(matrix, row, column);

    if (res == WRONG_MATRIX_ELEMENTS_ERROR)
    {
        printf("Wrong input data");
        return WRONG_MATRIX_ELEMENTS_ERROR;
    }

    int result = find_element(matrix, row, column);

    if (CANNOT_FIND_NUM == result)
        return CANNOT_FIND_NUM;
    
    printf("%d", result);

    return OK;
}