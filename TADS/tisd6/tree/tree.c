#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


struct tree_node_t* btree_insert(struct tree_node_t *tree, struct tree_node_t *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp(node->name, tree->name);
    if (cmp == 0)
    {
        assert(0);
    }
    else if (cmp < 0)
    {
        tree->left = btree_insert(tree->left, node);
    }
    else
    {
        tree->right = btree_insert(tree->right, node);
    }

    return tree;
}


struct tree_node_t* btree_lookup_1(struct tree_node_t *tree, const char *name)
{
    int cmp;

    if (tree == NULL)
        return NULL;

    cmp = strcmp(name, tree->name);
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return btree_lookup_1(tree->left, name);
    else
        return btree_lookup_1(tree->right, name);
}


struct tree_node_t* btree_lookup_2(struct tree_node_t *tree, const char *name)
{
    int cmp;

    while (tree != NULL)
    {
        cmp = strcmp(name, tree->name);

        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}


void btree_apply_pre(struct tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}


void btree_apply_in(struct tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_in(tree->left, f, arg);
    f(tree, arg);
    btree_apply_in(tree->right, f, arg);
}


void btree_apply_post(struct tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_post(tree->left, f, arg);
    btree_apply_post(tree->right, f, arg);
    f(tree, arg);
}


void btree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}
