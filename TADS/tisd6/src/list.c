#include "../headers/list.h"



int linsert(list_t **arr, char *buffer)
{
    if (!arr)
    {
        *arr = malloc(sizeof(list_t));
        (*arr)->value = malloc(sizeof(char) * (strlen(buffer) + 1));
        (*arr)->next = NULL;
        strcpy((*arr)->value, buffer);

        return 1;
    }

    list_t *temp = *arr;

    int depth = 1;

    while (temp->next)
    {
        depth++;
        temp = temp->next;
    }

    list_t *new_node = malloc(sizeof(list_t));
    new_node->next = NULL;
    new_node->value = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(new_node->value, buffer);

    temp->next = new_node;

    return depth;
}


static void free_list(list_t *node)
{
    if (node == NULL)
        return;

    free_list(node->next);

    free(node);
}


void free_list_arr(list_t *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free_list(arr[i].next);
    }

    free(arr);
}