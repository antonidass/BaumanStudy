#include "../headers/mem_manager.h"


node_t *allocate_node(void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    node->next = NULL;
    node->data = elem;

    return node;
}



void deallocate_list(node_t **head)
{    
    if (!(*head)->next)
    {
        free(*head);
        return;
    }

    node_t *temp;

    while ((*head)->next)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    free(*head);
}


void deallocate_array(int **data, int n)
{
    if (!data)
        return;

    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}