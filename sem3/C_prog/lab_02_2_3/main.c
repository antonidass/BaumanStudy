#include <stdio.h>
#include <math.h>

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define ONLY_SQUARE_ELEMENTS_ERROR -1
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10
#define SQUARE 1
#define NOT_SQUARE 0

int square_check(int num)
{
    int num2 = sqrt(num);
    double num1 = sqrt(num);

    if (fabs(num2 - num1) < EPS) 
        return SQUARE;

    return NOT_SQUARE;
}

int forming_array(int array[], int n)
{
    int i, j;

    for (i = j = 0; i < n; i++)
        if (!square_check(array[i]))
            array[j++] = array[i];
		
    if (j == 0)
        return ONLY_SQUARE_ELEMENTS_ERROR;

    return j;
}

void print_array(const int array[], const int n2)
{
    for (int i = 0; i < n2; i++)
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

    int n2 = forming_array(pa, n);

    if (n2 == ONLY_SQUARE_ELEMENTS_ERROR)
    {
        printf("Only square digits");
        return ONLY_SQUARE_ELEMENTS_ERROR;
    }

    print_array(pa, n2);

    return OK;
}