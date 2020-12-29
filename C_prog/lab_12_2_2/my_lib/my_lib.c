#include "my_lib.h"



void fill_fibonacci(int arr[], int n)
{
    if (n == 1)
    {
        arr[0] = 1;
        return;
    }

    arr[0] = arr[1] = 1;

    for (int i = 2; i < n; i++)
        arr[i] = arr[i - 1] + arr[i - 2];    
}



void fill_myarray(int src[], int nsrc, int dst[], int *ndst)
{
    *ndst = 0;
    int temp_ndst;
    int j;
    
    for (int i = 0; i < nsrc; i++)
    {
        temp_ndst = *ndst;

        for (j = 0; j < temp_ndst; j++)
            if (dst[j] == src[i])
                break;
        
        if (j == temp_ndst)
        {
            dst[j] = src[i];
            (*ndst)++;
        }
    }
}