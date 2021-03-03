#include "constants.h"
#include "work_with_list.h"



void front_back_split(node_t *head, node_t **back);

node_t *get_mid_node(node_t *head, int index_mid_elem);

int get_count_elems(node_t *head);

node_t *sorted_merge(node_t **head_a, node_t **head_b, comp_func_t comp);

int comp(const void *first, const void *second);

node_t *sort(node_t *head, comp_func_t comp);

node_t *get_remaining_elems(node_t **head);

int parse_args(int argc, char **argv, char *input_file_name);