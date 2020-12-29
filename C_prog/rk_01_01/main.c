#include <stdio.h>

#define N 1000
#define NO_POSITIVE -1
#define OK 0

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

int find_first_unic(int array[], int n)
{
    int first_unic;
    for (int i = 0; i < n; i++)
        if (array[i] > 0)
            return first_unic = array[i];
    return NO_POSITIVE;
}


int find_unic_numbers(int array[], int n)
{
    int first_unic_num = find_first_unic(array, n);

    if (first_unic_num == NO_POSITIVE)
        return NO_POSITIVE;

    int count = 1;

    for (int i = 0; i < n; i++)
    {
        if (array[i] > 0 && array[i] != first_unic_num)
        {
            count++;

            for (int j = i + 1; j < n; j++)
            {
                if (array[j] == array[i])
                    array[j] = first_unic_num;
            }
        }

    }
    return count;
}

int main()
{
    int array[N] = { 0 };

    int n = read_array(array);

    int res = find_unic_numbers(array, n);

    if (res == NO_POSITIVE)
    {   
        printf("0");
        return NO_POSITIVE;
    }

    printf("%d", res);

    return OK;
}