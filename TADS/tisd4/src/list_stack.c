#include "../headers/list_stack.h"



list_stack_t *list_stack_create()
{
    list_stack_t *list_stack = malloc(sizeof(list_stack_t));

    if (list_stack)
    {
        list_stack->val = (long)list_stack;
        list_stack->prev = NULL;
    }

    return list_stack;
}



int free_stack(list_stack_t **head, arr_of_free_areas *arr_f)
{
    while ((*head) != NULL)
    {
        delete_element_in_list_stack(head, arr_f);
    }

    return OK;
}

int add_element_in_list_stack(list_stack_t **head, int elem)
{  
    list_stack_t *node = list_stack_create(elem);

    node->index = (*head)->index + 1;
    node->prev = *head;
    *head = node;

    return OK;
}


long delete_element_in_list_stack(list_stack_t **head, arr_of_free_areas *arr_f)
{
    if ((*head) == NULL)
        return EMPTY_STACK;
    
    list_stack_t *temp = *head;

    long elem = (*head)->val;
    *head = (*head)->prev;

    arr_f->arr[++arr_f->ind] = (void*)temp;

    free(temp);

    return elem; 
}


void print_list_stack(list_stack_t *head_list_stack)
{   
    printf("\nЭлементы стека:\n\n  Вершина стека\n");
    while (head_list_stack != NULL)
    {
        printf("  0x%lx\n", head_list_stack->val);
        head_list_stack = head_list_stack->prev;
    }
}



int input_list_stack(int count, list_stack_t **head_list_stack)
{
    int rc;

    for (int i = 0; i < count; i++)
    {   
        if (*head_list_stack == NULL)
        {
            *head_list_stack = list_stack_create();
            (*head_list_stack)->index = 0;
        }
        else
        {
            rc = add_element_in_list_stack(head_list_stack, (*head_list_stack)->val);

            if (rc != OK)
                return rc;
        }
    }

    return OK;
}


void print_arr_free(arr_of_free_areas *arr_f)
{
    printf("\nМассив освободившихся областей :\n\n");

    for (int i = 0; i < arr_f->ind + 1; i++)
    {
        printf("  %p\n", arr_f->arr[i]);
    }
    printf("\n");
}


void shift_left(arr_of_free_areas *arr_f, int i)
{
    for (int j = i; j < arr_f->ind - 1; j++)
    {
        arr_f->arr[j] = arr_f->arr[j + 1];
    }
    
}

void check_arr_f(list_stack_t *head, arr_of_free_areas *arr_f)
{
    while (head != NULL)
    {
        int i = 0;
        while (i < arr_f->ind + 1)
        {
            if ((void *)head == arr_f->arr[i])
            {
                shift_left(arr_f, i);
                arr_f->ind--;
            }
            else
            {
                i++;
            }
        }
        head = head->prev;   
    }   
}