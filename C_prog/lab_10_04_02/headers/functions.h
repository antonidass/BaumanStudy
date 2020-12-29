#include "constants.h"
#include "iostream.h"
#include "mem_manager.h"
#include "list_ops.h"


list_num_node_t *parse_num(int num);

int handle_out_command();

int handle_mul_command();

int handle_sqr_command();

int handle_div_command();

list_num_node_t *mult_list_numbers(list_num_node_t *head_1, list_num_node_t *head_2);

list_num_node_t *sqr_list_num(list_num_node_t *head);

int get_num_from_list_num(list_num_node_t *head);