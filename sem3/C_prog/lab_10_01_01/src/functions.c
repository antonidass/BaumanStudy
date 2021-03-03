#include "../headers/functions.h"



int comp(const void *first, const void *second)
{
    LOG_DEBUG("first =  %d   secodn = %d", *((int *)first), *((int *)second)); 
    return *((int *)first) - *((int *)second);
}   


int get_count_elems(node_t *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }

    return count;
}


node_t *get_mid_node(node_t *head, int index_mid_elem)
{
    while (--index_mid_elem)
        head = head->next;
    
    return head;
}


void front_back_split(node_t *head, node_t **back)
{
    if (!head)
        return;

    int count = get_count_elems(head);
    LOG_DEBUG("count = %d", count);

    int mid_elem_index = count / 2 + count % 2;
    node_t *mid_node = get_mid_node(head, mid_elem_index);

    *back = mid_node->next;
    mid_node->next = NULL;
}




node_t *get_remaining_elems(node_t **head)
{
    node_t *remaining_elems_head = *head;
    *head = NULL;

    return remaining_elems_head;
}


node_t *sorted_merge(node_t **head_a, node_t **head_b, comp_func_t comp)
{
    if (!*head_a && !*head_b)
        return NULL;

    if (!*head_a)
        return get_remaining_elems(head_b);
    
    if (!*head_b)
        return get_remaining_elems(head_a);
    

    node_t *head_merged = NULL;

    if (comp((*head_a)->data, (*head_b)->data) < 0)
    {
        head_merged = *head_a;
        *head_a = (*head_a)->next;
        head_merged->next = sorted_merge(head_a, head_b, comp);
    }
    else
    {
        head_merged = *head_b;
        *head_b = (*head_b)->next;
        head_merged->next = sorted_merge(head_a, head_b, comp);        
    }

    return head_merged;
}


node_t *sort(node_t *head, comp_func_t comp)
{
    if (!head || !head->next)
        return head;

    node_t *back;
    front_back_split(head, &back);

    head = sort(head, comp);
    back = sort(back, comp);

    return sorted_merge(&head, &back, comp);
}


int parse_args(int argc, char **argv, char *input_file_name)
{
    if (argc > 2 || argc < 1)
        return ERROR_ARGS;

    strcpy(input_file_name, argv[1]);
    
    return OK;
}