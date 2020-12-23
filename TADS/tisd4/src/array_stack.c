#include "../headers/array_stack.h"




int add_element_in_arr_stack(array_stack_t *arr_stack, long elem)
{
    if (++arr_stack->elems_count == arr_stack->capacity)
        return STACK_OVERFLOW;

    arr_stack->arr[arr_stack->elems_count] = elem;

    return OK;
}



int input_arr_stack(int count, array_stack_t *arr_stack)
{
    int rc;
    unsigned long elem;
    for (int i = 0; i < count; i++)
    {
        rc = scanf("%lx", &elem);

        if (rc != 1 || elem > 10000000000000)   
            return ERROR_IN_INPUT_DATA;

        rc = add_element_in_arr_stack(arr_stack, elem);

        if (rc == STACK_OVERFLOW)
            return rc;
    }

    return OK;
}


long delete_element_in_arr_stack(array_stack_t *arr_stack)
{
    if (arr_stack->elems_count == -1)
        return EMPTY_STACK;
    
    return arr_stack->arr[arr_stack->elems_count--];
}



void print_arr(const array_stack_t *arr_stack)
{
    printf("\nЭлементы стека:\n\n  Вершина стека\n");
    for (int i = arr_stack->elems_count; i >= 0; i--)
        printf("  0x%lx\n", arr_stack->arr[i]);

    printf("\n");
}



void generate(array_stack_t *arr_stack, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr_stack->arr[++arr_stack->elems_count] = (rand() % 10000000000) * 100000;
    }
}