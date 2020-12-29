#include <stdio.h> 

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10

int read_array(int *start_ponter, int *end_ponter)
{
    int rc;

    for (int *i = start_ponter; i < end_ponter; i++)
    {
        rc = scanf("%d", i);
        if (rc != 1)
            return WRONG_ARRAY_ELEMENTS_ERROR;
    }

    return OK;
}

int max_pair(int *start_pointer, int *end_ponter)
{
    int max_pair = *start_pointer + *(--end_ponter);

    while (++start_pointer <= --end_ponter)
    {
        if (*start_pointer + *end_ponter > max_pair)
        {
            max_pair = *start_pointer + *end_ponter;
        }
    }
    
    return max_pair;
}

int main()
{
    int array[N];
    int n;
    int res;

    printf("Enter the size of the array ");
    res = scanf("%d", &n);

    if (res != 1 || n > MAX_SIZE || n < MIN_SIZE)
    {
        printf("Wrong array length");
        return WRONG_ARRAY_LENGTH_ERROR;
    }

    int *end_pointer = &array[n], *start_pointer = array;

    res = read_array(start_pointer, end_pointer);

    if (res == WRONG_ARRAY_ELEMENTS_ERROR)
    {
        printf("Wrong input data");
        return WRONG_ARRAY_ELEMENTS_ERROR;
    }

    int ans = max_pair(start_pointer, end_pointer);

    printf("Answer = %d", ans);

    return OK;
}