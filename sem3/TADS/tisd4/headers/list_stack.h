#include "constants.h"
#include "data_structures.h"


int input_list_stack(int count, list_stack_t **head_list_stack);
void print_list_stack(list_stack_t *head_list_stack);
int add_element_in_list_stack(list_stack_t **head, int elem);
int free_stack(list_stack_t **head, arr_of_free_areas *arr_f);
list_stack_t *list_stack_create();
long delete_element_in_list_stack(list_stack_t **head, arr_of_free_areas *arr_f);
void print_arr_free(arr_of_free_areas *arr_f);
void check_arr_f(list_stack_t *head, arr_of_free_areas *arr_f);

