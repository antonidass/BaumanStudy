#include "constants.h"
#include "common_data_structures.h"


typedef struct
{
    task_t *arr;
    task_t *pin;
    task_t *pout;
    int capacity;
    int cur_size;
} array_queue_t;



int isFull_arr_queue(const array_queue_t *queue);

int isEmpty_arr_queue(const array_queue_t *queue);

int isFrontFull_arr_queue(const array_queue_t *queue);

void print_arr_queue(const array_queue_t *queue);

int create_arr_queue(array_queue_t *queue, int capacity);

int push_arr_queue(array_queue_t *queue, task_t elem);

int pop_arr_queue(array_queue_t *queue, task_t *deleted_elem);

void delete_arr_queue(array_queue_t *queue);