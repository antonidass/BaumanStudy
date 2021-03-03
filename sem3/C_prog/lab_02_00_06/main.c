#include <stdio.h> 
#include <sys/times.h>
#include <time.h>

#define WRONG_ARRAY_LENGTH_ERROR 1
#define WRONG_ARRAY_ELEMENTS_ERROR 2
#define OK 0
#define MAX_SIZE 10000000
#define MIN_SIZE 1
#define EPS 1e-5
#define N 10
#define MAX_POSSIBLE_TIME 2147483647
#define REPEATS 10000

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

int process_1(const int array[], const int n)
{
    int max_pair = array[0] + array[n-1];

    for (int i = 1; i <= (n - 1) / 2; i++)
    {
        if (array[i] + array[n-i-1] > max_pair)
        {
            max_pair = array[i] + array[n-i-1];
        }
    }

    return max_pair;
}

int process_2(const int *array_pointer, const int n)
{
    int max_pair = *array_pointer + *(array_pointer + n - 1);

    for (int i = 1; i <= (n - 1) / 2; i++)
    {
        if (*(array_pointer + i) + *(array_pointer + n - i - 1) > max_pair)
        {
            max_pair = *(array_pointer + i) + *(array_pointer + n - i - 1);
        }
    }

    return max_pair;
}

int process_3(const int *start_pointer, const int n)
{
    const int *end_ponter = start_pointer + n;

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

double counting_time(int array[], int n, long long repeats, int (*process)(const int *, const int))
{
    struct tms tmsBegin, tmsEnd;

    double elapsed_time;

    long double max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0; 
	
    for (int i = 0; i < repeats; i++)
    {
        times(&tmsBegin);
        process(array, n);
        times(&tmsEnd);
        
        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;

        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
		
        if (elapsed_time > max_time)
            max_time = elapsed_time;
		
    }

    return (sum - max_time - min_time) / (repeats - 2);
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

    double time1 = counting_time(array, n, REPEATS, process_1);
    double time2 = counting_time(array, n, REPEATS, process_2);
    double time3 = counting_time(array, n, REPEATS, process_3);
	
    printf("Process_1 time = %.7lf us, Process_2 time = %.7lf us, Process_3 time = %.7lf us", time1, time2, time3);

    return OK;
}