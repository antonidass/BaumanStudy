#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"



struct tree_node_t* node_create(const char *name)
{
    struct tree_node_t *node;

    node = malloc(sizeof(struct tree_node_t));
    
    if (node)
    {
        node->name = name;

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}


void node_print(struct tree_node_t *node, void *param)
{
    const char *fmt = param;

    printf(fmt, node->name);
}


void node_free(struct tree_node_t *node, void *param)
{
    free(node);
}


void node_to_dot(struct tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);
}
