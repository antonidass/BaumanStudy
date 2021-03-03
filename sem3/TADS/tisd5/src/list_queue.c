#include "../headers/list_queue.h"


int isFull_list_queue(const list_queue_t *queue)
{
    if (queue->capacity == queue->cur_size)
        return QUEUE_OVERFLOW;

    return OK;    
}


int isEmpty_list_queue(const list_queue_t *queue)
{
    if (queue->cur_size == 0)
        return EMPTY_QUEUE;

    return NOT_EMPTY;
}


void print_list_queue(const list_queue_t *queue)
{

    if (isEmpty_list_queue(queue))
    {
        printf("Очередь пуста!\n\n");
        return;
    }

    node_queue_t *temp = queue->head;

    printf("\nГолова очереди\n");
    for (int i = 0; i < queue->cur_size; i++)
    {
        printf("i = %3d   значение элемента = %lf  |  адрес элемента %p\n", i+1, temp->task.time, (void*)(temp));
        temp = temp->next;
    }
    printf("Хвост очереди\n\n");
}


int create_list_queue(list_queue_t *queue, int capacity)
{
    queue->head = NULL;
    queue->tail = NULL;
    queue->cur_size = 0;
    queue->capacity = capacity;
}


int push_list_queue(list_queue_t *queue, task_t elem)
{
    if (isFull_list_queue(queue))
        return QUEUE_OVERFLOW;

    
    node_queue_t *node = malloc(sizeof(node_queue_t));
    node->task = elem;
    node->next = NULL;

    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = queue->head;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->cur_size++;

    return OK;
}


int pop_list_queue(list_queue_t *queue, task_t *deleted_elem)
{
    if (isEmpty_list_queue(queue))
        return EMPTY_QUEUE;

    *deleted_elem = queue->head->task;
    node_queue_t *temp = queue->head->next;
    free(queue->head);
    queue->head = temp;
    queue->cur_size--;

    return OK;
}


void delete_list_queue(list_queue_t *queue)
{
    node_queue_t *temp;
    while (queue->head != NULL)
    {
        temp = queue->head->next;
        free(queue->head);
        queue->head = temp;
    }
}

