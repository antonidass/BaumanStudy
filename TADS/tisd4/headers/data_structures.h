#include "constants.h"




#ifndef DATA_S
#define DATA_S

typedef struct
{
    long arr[MAX_STACK_SIZE];
    int elems_count;
    int capacity;
} array_stack_t;


typedef struct list_stack_t list_stack_t;

struct list_stack_t
{
    long val;
    list_stack_t *prev;
    int index;
};



typedef struct 
{
    void *arr[MAX_STACK_SIZE];
    int ind;
} arr_of_free_areas;


#endif