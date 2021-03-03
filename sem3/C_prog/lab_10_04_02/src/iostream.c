#include "../headers/iostream.h"


int input_command()
{
    commands_t command;

    char input[MAX_STRING_LEN];

    int rc = scanf("%s", input);

    if (rc != 1)
        return ERROR_IN_INPUT_COMMAND;
        
    if (!strcmp(input, "out"))
        command = out;
    else if (!strcmp(input, "mul"))
        command = mul;
    else if (!strcmp(input, "sqr"))
        command = sqr;
    else if (!strcmp(input, "div"))
        command = div_;
    else
        return ERROR_IN_INPUT_COMMAND;

    return command;
}


int input_num(int *num)
{
    int rc = scanf("%d", num);

    if (rc != 1 || *num <= 1)
        return ERROR_IN_INPUT_NUM;
    
    return OK;
}


void print_list(list_num_node_t *head)
{
    if (!head)
        return;

    list_num_node_t *tail = get_tail(head);

    while (tail)
    {
        printf("%d %d ", tail->num, tail->pow);
        tail = tail->prev;
    }
    
    printf("1");
}