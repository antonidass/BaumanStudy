#include <stdio.h>
#include <math.h>

#define WRONG_MATRIX_LENGTH_ERROR 1
#define WRONG_MATRIX_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define N 10
#define M 10

int find_odd_digit_sum(int num)
{
    num = fabs(num);
    int sum = num % 10;

    while (num /= 10)
        sum += num % 10;
    
    return sum % 2;
}

void print_special_row(const int len)
{
    for (int i = 0; i < len; i++)
        printf("-1 ");
    
    printf("\n");
}

void print_matrix_row(int matrix[][M], const int row, const int column)
{
    for (int j = 0; j < column; j++)
        printf("%d ", matrix[row][j]);
    
    printf("\n");
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

void handle_matrix(int matrix[][M], const int row, const int column)
{
    for (int i = 0; i < row; i++)
    {   
        int count = 0;
        for (int j = 0; j < column; j++)
        {
            count += find_odd_digit_sum(matrix[i][j]);

            if (count >= 2)
            {
                print_special_row(column);
                break;
            }
        }

        print_matrix_row(matrix, i, column);
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

    handle_matrix(matrix, row, column);

    return OK;
}