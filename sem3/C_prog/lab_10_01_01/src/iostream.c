#include "../headers/iostream.h"



void print_list(const node_t *head)
{        
    while (head)
    {
        printf("%d ", *(int *)(head->data));
        head = head->next;
    }
}


int input_data(FILE *file, int *data_arr[], node_t **head)
{
    int num, i = 0;

    while (fscanf(file, "%d", &num) != EOF)
    {
        data_arr[i] = malloc(sizeof(int));
        *data_arr[i] = num; 

        push_back(head, data_arr[i]);
        i++;
    }

    return i;
}