#include <stdio.h>

#define WRONG_MATRIX_LENGTH_ERROR 1
#define WRONG_MATRIX_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define N 10
#define M 10
#define YES 1
#define NO 0


void print_matrix(int matrix[][M], const int row, const int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
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


int is_prime_number(int num)
{
    int k = 2;

    if (num <= 1)
        return NO;

    while (k * k <= num)
    {
        while (num % k == 0)
            return NO;
        k++;
    }

    return YES;
}

void form_matrix(int matrix[][M], int row, int column, int array[])
{
    int i_array = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (is_prime_number(matrix[i][j]))
                matrix[i][j] = array[i_array++];
        }
    }
}

int form_array(int matrix[][M], int row, int column, int array[])
{
    int i_array = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (is_prime_number(matrix[i][j]))
                array[i_array++] = matrix[i][j];
        }
    }
    
    return i_array;
}

void swap(int *p_first, int *p_second)
{
    int t = *p_first;
    *p_first = *p_second;
    *p_second = t;
}

void reverse_array(int array[], int n)
{
    for (int i = 0; i < n / 2; i++)
        swap(&array[i], &array[n - i - 1]); 
}

void print_array(const int array[], const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}


int main()
{
    int matrix[N][M];
    int row, column;
    int res;

    printf("Enter the size of the matrix ");
    res = scanf("%d%d", &row, &column);

    if (res != 2 || row > MAX_SIZE || row < MIN_SIZE + 1 || column > MAX_SIZE || column < MIN_SIZE)
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

    int array[N * M];

    int n = form_array(matrix, row, column, array);

    reverse_array(array, n);

    form_matrix(matrix, row, column, array);

    print_matrix(matrix, row, column);

    return OK;
}