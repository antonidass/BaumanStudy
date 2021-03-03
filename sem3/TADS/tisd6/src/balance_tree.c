#include "../headers/balance_tree.h"


void tree_depth(tree_node_t *root, int *vrtxs, int *cmprs, int depth)
{
    if (!root)
    {
        return;
    }
    (*vrtxs)++;
    (*cmprs) += depth;

    tree_depth(root->right, vrtxs, cmprs, depth + 1);
    tree_depth(root->left, vrtxs, cmprs, depth + 1);
}

void push_back(arr_t *arr, tree_node_t *to_add)
{
    arr->size++;
    if (arr->size >= arr->mem_size)
    {
        arr->mem_size *= 2;
        arr->arr = realloc(arr->arr, arr->mem_size * sizeof(tree_node_t *));
    }

    for (int i = arr->size; i > 0; i--)
    {
        arr->arr[i] = arr->arr[i - 1];
    }

    arr->arr[0] = to_add;
}


void store_nodes(tree_node_t *root, arr_t *arr)
{
    if (root == NULL)
    {
        return;
    }

    store_nodes(root->left, arr);
    push_back(arr, root);
    store_nodes(root->right, arr);
}



tree_node_t *build_tree(arr_t *arr, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    tree_node_t *root = arr->arr[mid];

    root->right = build_tree(arr, start, mid - 1);
    root->left = build_tree(arr, mid + 1, end);

    return root;
}



tree_node_t *balance_tree(tree_node_t *root, int *unique)
{
    arr_t arr;
    arr.mem_size = 8;
    arr.size = 0;
    arr.arr = malloc(sizeof(tree_node_t *) * arr.mem_size);
    store_nodes(root, &arr);

    int n = arr.size;
    *unique = n;

    tree_node_t *r = build_tree(&arr, 0, n - 1);

    free(arr.arr);

    return r;
}