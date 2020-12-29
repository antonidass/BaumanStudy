#include "../headers/list_ops.h"



void push_back(list_num_node_t **head, int num, int pow)
{
    list_num_node_t *node = allocate_list_num_node(num, pow);
    
    if (!*head)
    {
        *head = node;
        (*head)->prev = NULL;
    }
    else
    {
        list_num_node_t *tail = get_tail(*head);
        node->prev = tail;
        tail->next = node;
    }
}


list_num_node_t *get_tail(list_num_node_t *head)
{
    if (!head->next)
        return head;
    
    while (head->next && (head = head->next)) ;

    return head;
}


