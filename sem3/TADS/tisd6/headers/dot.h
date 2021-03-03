#include "constants.h"
#include "binary_tree.h"


#ifndef DOT
#define DOT

typedef void (*ptr_action_t)(tree_node_t*, void*);


void btree_apply_pre(tree_node_t *tree, ptr_action_t f, void *arg);

void node_to_dot(tree_node_t *tree, void *param);

void btree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree);

void out_btree_dot(tree_node_t *root, char *name);


#endif