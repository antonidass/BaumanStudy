#include "constants.h"


#ifndef __TREE_NODE_H__

#define __TREE_NODE_H__


typedef struct tree_node tree_node_t;
struct tree_node
{
    char *data;
    tree_node_t *left;
    tree_node_t *right;
};


void node_print(tree_node_t *node);

tree_node_t *node_create(const char *data);

void node_free(tree_node_t *node, void *param);

tree_node_t *btree_insert(tree_node_t *tree, tree_node_t *node);

tree_node_t *delete_node(tree_node_t *node, char data[]);

int search_tree(char *to_find, tree_node_t root);


#endif