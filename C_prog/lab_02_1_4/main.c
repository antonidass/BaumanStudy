#include <stdio.h>

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10

void print_array(const int array[], const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}

int read_array(int array[], const int n)
{
    int rc;

    for (int i = 0; i < n; i++)
    {
        rc = scanf("%d", &array[i]);
        if (rc != 1)
            return WRONG_ARRAY_ELEMENTS_ERROR;
    }

    return OK;
}

void insert_sorting(int array[], const int n)
{  
    for (int i = 0; i < n; i++)
    {
        int j = i - 1;
        int x = array[i];

        for (; j >= 0 && x < array[j]; j--)
        {
            array[j + 1] = array[j];
        }

        array[j + 1] = x;
    }
}

int main()
{
    int array[N], *pa = array;
    int n;
    int res;

    printf("Enter the size of the array ");
    res = scanf("%d", &n);

    if (res != 1 || n > MAX_SIZE || n < MIN_SIZE)
    {
        printf("Wrong array length");
        return WRONG_ARRAY_LENGTH_ERROR;
    }

    res = read_array(pa, n);

    if (res == WRONG_ARRAY_ELEMENTS_ERROR)
    {
        printf("Wrong input data");
        return WRONG_ARRAY_ELEMENTS_ERROR;
    }

    insert_sorting(pa, n);

    print_array(pa, n);

    return OK;
}