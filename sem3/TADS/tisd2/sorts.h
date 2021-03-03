#pragma once
#include "data_structures.h"
#include "constants.h"


void swap_flats(flat_t *first, flat_t *second);
void bubble_sort_for_value(flat_t flats[], int n);
void swap_keys(int *first, int *second);
void bubble_sort_for_key(flat_t flats[], int n, int keys[]);
void quick_sort_for_value(flat_t flats[], int first, int last);
void quick_sort_for_keys(flat_t flats[], int first, int last, int keys[]);