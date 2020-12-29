#include "../headers/work_with_list.h"
#include "../headers/mem_manager.h"



node_t *get_penultimate_node(node_t *head)
{
    if (!head->next)
        return NULL;

    while (head->next->next)
        head = head->next;

    return head;
}


node_t *get_last_node(node_t *head)
{
    if (!head->next)
        return head;
    
    while (head->next && (head = head->next)) ;

    return head;
}


void *pop_back(node_t **head)
{
    if (!head || *head == NULL)
        return NULL;

    node_t *penultimate = get_penultimate_node(*head);
    void *data = NULL;
    node_t *temp_pointer = *head;

    if (!penultimate)
    {
        data = (*head)->data;
        *head = NULL;
    }
    else
    {
        data = penultimate->next->data;
        temp_pointer = penultimate->next;
        penultimate->next = NULL;
    }
    
    free(temp_pointer);

    return data;
}


void push_back(node_t **head, void *elem)
{
    node_t *node = allocate_node(elem);

    if (!*head)
    {
        *head = node;
    }
    else
    {
        node_t *last_node = get_last_node(*head);
        last_node->next = node;
    }
}


void insert(node_t **head, node_t *elem, node_t *before)
{
    if (!elem || !before || !head || !*head)
        return;

    node_t *temp = *head;
    
    if (before == *head)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    while (temp->next && temp->next != before)
        temp = temp->next;
    
    LOG_DEBUG("empty - > %d ", !temp->next);

    if (!temp->next)
        return;

    temp->next = elem;
    temp->next->next = before;
}


node_t *reverse(node_t *head)
{
    if (!head)
        return NULL;

    LOG_DEBUG("head.data = %d", *(int*)head->data);
    if (!head->next)
        return head;

    node_t *rev_head = reverse(head->next);

    node_t *node = get_last_node(rev_head);
    node->next = head;
    head->next = NULL;

    LOG_DEBUG("node = %d  rev.data = %d", *(int *)node->data, *(int *)rev_head->data);

    return rev_head;
}