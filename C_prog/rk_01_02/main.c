#include <stdio.h>

#define N 1000
#define M 1000
#define NO_POSITIVE -1
#define OK 0
#define NO_EVENS 1


int read_array(int array[])
{   
    int i = 0;
    int rc;
    while (1)
    {   
        rc = scanf("%d", &array[i]);

        if (rc == 0)
            break;
    
        printf("%d ", array[i]);
        i++;
    }
    
    return i;
}

int find_max_num(int array[], int n)
{
    int max_num = array[0];
    
    for (int i = 1; i < n; i++)
    {
        if (array[i] > max_num)
            max_num = array[i];
    }
    return max_num;
}

int find_cols(int max_num)
{   
    
    int count = 0;
    while(max_num /= 10)
        count++;

    return count + 1;
}

int create_matrix(int array[], int n, int matrix[][M])
{
    int max_num = find_max_num(array, n);

    int columns = find_cols(max_num);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = array[i] % 10;
            array[i] /= 10;
        }
    }

    return columns;
}

int find_first_min_even(int matrix[][M], const int rows, const int columns)
{
    int first_even = NO_EVENS;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix[i][j] % 2 == 0 && matrix[i][j] != 0)
            {
                first_even = matrix[i][j];
                break;
            }
        }
    }

    return first_even;   
}



int find_min_even(int matrix[][M], const int rows, const int columns)
{

    int min_even = find_first_min_even(matrix, rows, columns);

    if (min_even == NO_EVENS)
        return NO_EVENS;

    int min_row;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix[i][j] <= min_even && matrix[i][j] % 2 == 0 && matrix[i][j] != 0)
            {
                min_even = matrix[i][j];
                min_row = i;
            }

        }
    }
    
    return min_row;
}

void print_matrix(int matrix[][M], int rows, int cols)
{
    printf("M   N   L \n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d   %d   %d \n", i, j, matrix[i][j]);
        }
    }
}

int main()
{
    int array[N] = { 0 };
    int n = read_array(array);
    int matrix[N][M];

    int columns = create_matrix(array, n, matrix);

    int res = find_min_even(matrix, n, columns);

    if (res == NO_EVENS)
        return NO_EVENS;
    
    printf("min even = %d \n", res + 1);

    print_matrix(matrix, n, columns);

    return res;
}