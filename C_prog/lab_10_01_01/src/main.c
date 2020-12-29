#include "../headers/constants.h"
#include "../headers/functions.h"
#include "../headers/iostream.h"
#include "../headers/mem_manager.h"
#include "../headers/work_with_list.h"


/*
Из файла считываются целочисленные значения в односвязный список
Затем происходит reverse списка 
Затем удаляется один элемент из конца списка
Затем вставляется элемент со значением -1 в начало списка
Затем сортируется и выводится на экран список 

Гарантируется что в файле больше двух чисел и все элементы целочисленные!
*/


int main(int argc, char **argv)
{
    char input_file_name[MAX_FILE_NAME];

    int rc = parse_args(argc, argv, input_file_name);

    if (rc != OK)
        return rc;
    

    FILE *file = fopen(input_file_name, "r");

    if (!file)
        return ERROR_IN_OPEN_FILE;

    int **data = malloc(sizeof(int *) * MAX_ELEMS_IN_FILE);
    node_t *head = NULL;

    int n = input_data(file, data, &head);


    node_t *rev_head = reverse(head);

    int *a = malloc(sizeof(int));
    *a = -1;

    node_t *elem = allocate_node(a);


    insert(&rev_head, elem, rev_head);

    node_t *head_soted = sort(rev_head, comp);


    print_list(head_soted);

    deallocate_list(&head_soted);
    free(a);
    deallocate_array(data, n);
    fclose(file);
    
    return OK;
}