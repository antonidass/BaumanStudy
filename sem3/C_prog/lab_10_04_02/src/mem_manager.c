#include "../headers/mem_manager.h"


list_num_node_t *allocate_list_num_node(int num, int power)
{
    list_num_node_t *node = malloc(sizeof(list_num_node_t));
    node->next = NULL;
    node->num = num;
    node->pow = power;

    return node;
}


void deallocate_list_num_node(list_num_node_t **head)
{
    if (!(*head)->next)
    {
        free(*head);
        return;
    }

    list_num_node_t *temp;

    while ((*head)->next)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    
    free(*head);
}