#include "constants.h"
#include "work_with_list.h"



void deallocate_list(node_t **head);

node_t *allocate_node(void *elem);

void deallocate_node(node_t **head, node_t *node);

void deallocate_array(int **data, int n);