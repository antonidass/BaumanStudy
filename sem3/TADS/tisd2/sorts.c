#include "sorts.h"


void swap_flats(flat_t *first, flat_t *second)
{
    flat_t tmp = *first;
    *first = *second;
    *second = tmp;
}

void bubble_sort_for_value(flat_t flats[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (flats[j].price_per_meter > flats[j+1].price_per_meter)
                swap_flats(&flats[j], &flats[j+1]);
        }
    }
}

void swap_keys(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void bubble_sort_for_key(flat_t flats[], int n, int keys[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (flats[keys[j]].price_per_meter > flats[keys[j+1]].price_per_meter)
                swap_keys(&keys[j], &keys[j+1]);
        }
    }
}

void quick_sort_for_value(flat_t flats[], int first, int last)
{
    int l = first;
    int r = last;
    int m = flats[(l + r) / 2].price_per_meter;

    while (l <= r)
    {
        while (flats[l].price_per_meter < m)
            l++;
        while (flats[r].price_per_meter > m)
            r--;
        if (l <= r)
            swap_flats(&flats[l++], &flats[r--]);
    }

    if (first < r)
        quick_sort_for_value(flats, first, r);
    
    if (last > l)
        quick_sort_for_value(flats, l, last);
}

void quick_sort_for_keys(flat_t flats[], int first, int last, int keys[])
{
    int l = first;
    int r = last;
    int m = flats[keys[(l + r) / 2]].price_per_meter;

    while (l <= r)
    {
        while (flats[keys[l]].price_per_meter < m)
            l++;
        while (flats[keys[r]].price_per_meter > m)
            r--;
        if (l <= r)
            swap_keys(&keys[l++], &keys[r--]);
    }

    if (first < r)
        quick_sort_for_keys(flats, first, r, keys);
    
    if (last > l)
        quick_sort_for_keys(flats, l, last, keys);
}