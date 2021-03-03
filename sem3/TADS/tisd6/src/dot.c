#include "../headers/dot.h"


void btree_apply_pre(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}


void btree_apply_in(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_in(tree->left, f, arg);
    f(tree, arg);
    btree_apply_in(tree->right, f, arg);
}


void btree_apply_post(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_post(tree->left, f, arg);
    btree_apply_post(tree->right, f, arg);
    f(tree, arg);
}


void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->data, tree->right->data);
}


void btree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    btree_apply_pre(tree, node_to_dot, f);
    fprintf(f, "}\n");
}


void out_btree_dot(tree_node_t *root, char *name)
{
    FILE *f = fopen(name, "w");
    btree_export_to_dot(f, "tree", root);
    fclose(f);
}



