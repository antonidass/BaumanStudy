#include "../headers/binary_tree.h"



tree_node_t *btree_insert(tree_node_t *tree, tree_node_t *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp(node->data, tree->data);
    // printf("cmp = %d   node.data = %s   tree_data = %s\n", cmp, node->data, tree->data);
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


tree_node_t *node_create(const char *data)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    size_t len;

    if (node)
    {
        len = strlen(data);    
        node->data = malloc(sizeof(char) * len);
        strcpy(node->data, data);    

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}



tree_node_t *min_value_node(tree_node_t *node)
{
   tree_node_t *current = node;

   while (current && current->left != NULL)
      current = current->left;

    // printf("cur _data = %s\n", current->data);
   return current;
}


tree_node_t *delete_node(tree_node_t *root, char data[])
{
    if (!root)
        return root;

    int cmp = strcmp(data, root->data);

    if (cmp < 0)
        root->left = delete_node(root->left, data);

    else if (cmp > 0)
        root->right = delete_node(root->right, data);

    else
    {
        if (root->left == NULL)
        {
            tree_node_t *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            tree_node_t *temp = root->left;
            free(root);
            return temp;
        }

        tree_node_t *temp = min_value_node(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }

   return root;
}



void node_print(tree_node_t *node)
{
    printf("deleted_node = %s\n", node->data);
}



int search_tree(char *to_find, tree_node_t root)
{
    int i = 0;
    tree_node_t *p = &root;

    while (p != NULL)
    {
        i++;
        if (strcmp(p->data, to_find) == 0)
            return i;

        // printf("pdata = %s    to_find = %s\n", p->data, to_find);
        if (strcmp(p->data, to_find) < 0)
            p = p->right;
        else
            p = p->left;
    }

    return NOT_FOUND;
}