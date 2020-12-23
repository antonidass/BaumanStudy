#include "constants.h"
#include "common_data_structures.h"


#ifndef LIST_QUEUE_DATAS
#define LIST_QUEUE_DATAS

typedef struct node_queue_t node_queue_t;
struct node_queue_t
{
    task_t task;
    node_queue_t *next;
};


typedef struct
{
    node_queue_t *head;
    node_queue_t *tail;
    int capacity;
    int cur_size;
} list_queue_t;


#endif


int isFull_list_queue(const list_queue_t *queue);

int isEmpty_list_queue(const list_queue_t *queue);

void print_list_queue(const list_queue_t *queue);

int create_list_queue(list_queue_t *queue, int capacity);

int push_list_queue(list_queue_t *queue, task_t elem);

int pop_list_queue(list_queue_t *queue, task_t *deleted_elem);

void delete_list_queue(list_queue_t *queue);