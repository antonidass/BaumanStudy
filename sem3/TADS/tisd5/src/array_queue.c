#include "../headers/array_queue.h"



int create_arr_queue(array_queue_t *queue, int capacity)
{
    queue->arr = malloc(sizeof(task_t) * capacity);
    queue->cur_size = 0;
    queue->capacity = capacity;
    queue->pin = queue->arr;
    queue->pout = queue->arr;
}


int isFull_arr_queue(const array_queue_t *queue)
{
    if (queue->cur_size == queue->capacity)
        return QUEUE_OVERFLOW;

    return OK;
}


int isEmpty_arr_queue(const array_queue_t *queue)
{
    if (queue->cur_size == 0)
        return EMPTY;
    
    return NOT_EMPTY;
}


void print_arr_queue(const array_queue_t *queue)
{

    if (isEmpty_arr_queue(queue))
    {
        printf("Очередь пуста!\n\n");
        return;
    }


    printf("\nГолова очереди\n");
    for (int i = 0; i < queue->capacity; i++)
    {
        if (queue->pin <= queue->pout)
        {
            if (i >= queue->pin - queue->arr && i < queue->pout - queue->arr)
                printf("i = %3d   свободная область памяти      |  адрес области %p\n", i+1, (void*)(queue->arr + sizeof(task_t) * i));
            else
                printf("i = %3d   значение элемента = %lf  |  адрес элемента %p\n", i+1, queue->arr[i].time, (void*)(queue->arr + sizeof(task_t) * i));
        }
        else
        {
            if (i >= queue->pout - queue->arr && i < queue->pin - queue->arr)
                printf("i = %3d   значение элемента = %lf  |  адрес элемента %p\n", i+1, queue->arr[i].time, (void*)(queue->arr + sizeof(task_t) * i));
            else
                printf("i = %3d   свободная область памяти      |  адрес области %p\n", i+1, (void*)(queue->arr + sizeof(task_t) * i));
        }


    }
    printf("Хвост очереди\n\n");
}


int isFrontFull_arr_queue(const array_queue_t *queue)
{
    if (queue->capacity == queue->pin - queue->arr)
        return FRONT_OVERFLOW;

    return OK;
}


int push_arr_queue(array_queue_t *queue, task_t elem)
{
    if (isFull_arr_queue(queue))
        return QUEUE_OVERFLOW;

    if (isFrontFull_arr_queue(queue))
        queue->pin = queue->arr;

    *queue->pin++ = elem;
    queue->cur_size++;

    return OK;
}


int pop_arr_queue(array_queue_t *queue, task_t *deleted_elem)
{
    if (isEmpty_arr_queue(queue))
        return EMPTY_QUEUE;
    
    *deleted_elem = *queue->pout;

    queue->cur_size--;
    queue->pout++;

    if (queue->pout - queue->arr == queue->capacity)
        queue->pout = queue->arr;    

    return OK;
}



void delete_arr_queue(array_queue_t *queue)
{
    free(queue->arr);
}