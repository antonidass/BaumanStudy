#include <stdio.h>

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define NO_MATCHING_ELEMENTS_ERROR 3
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10


/* first_digit: поиск первой цифры числа */
int first_digit(int num)
{
    int first_digit;

    while (num > 9)
        num /= 10;

    first_digit = num % 10;
		
    return first_digit;
}

int forming_array(const int array[], const int n, int formed_array[])
{	
    int last_digit;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        last_digit = array[i] % 10;

        if (first_digit(array[i]) == last_digit)
            formed_array[j++] = array[i];
    }

    if (j == 0)
        return NO_MATCHING_ELEMENTS_ERROR;

    return j;
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


void print_array(const int array[], const int n2)
{
    for (int i = 0; i < n2; i++)
        printf("%d ", array[i]);
}

int main()
{
    int array[N], *pa = array;
    int n, n2;
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

    int formed_array[N], *pf = formed_array;
	
    n2 = forming_array(pa, n, pf);

    if (n2 == NO_MATCHING_ELEMENTS_ERROR)
    {
        printf("No matching digits");
        return NO_MATCHING_ELEMENTS_ERROR;
    }

    print_array(pf, n2);

    return OK;
}