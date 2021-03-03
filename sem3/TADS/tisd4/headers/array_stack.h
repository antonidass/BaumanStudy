#include "constants.h"
#include "data_structures.h"


void print_arr(const array_stack_t *arr_stack);
long delete_element_in_arr_stack(array_stack_t *arr_stack);
int input_arr_stack(int count, array_stack_t *arr_stack);
int add_element_in_arr_stack(array_stack_t *arr_stack, long elem);
void copy_array_rev_stack(array_stack_t *dst, array_stack_t *src);
void generate(array_stack_t *arr_stack, int n);