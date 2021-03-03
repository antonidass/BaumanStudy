#include <stdio.h>
#include <math.h>

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define NO_NEGATIVE_ELEMENTS_ERROR 3
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10

float finding_average(const int array[], const int n)
{
    float average = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
        if (array[i] < 0)
        {
            average += array[i];
            count++;
        }

    if (fabsf(average) <= EPS)
        return NO_NEGATIVE_ELEMENTS_ERROR;

    average /= count;

    return average;
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

    float ans = finding_average(pa, n);
	
    if (fabsf(ans - NO_NEGATIVE_ELEMENTS_ERROR) < EPS)
    {
        printf("No negative elements");
        return NO_NEGATIVE_ELEMENTS_ERROR;
    }

    printf("Average = %.5f", ans);

    return OK;
}