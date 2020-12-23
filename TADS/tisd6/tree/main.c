#include <assert.h>
#include <stdio.h>
#include "tree.h"


int main(void)
{
    struct tree_node_t *root = NULL;
    struct tree_node_t *node;

    node = node_create("f");
    assert(node);
    assert(btree_lookup_1(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("b");
    assert(node);
    assert(btree_lookup_1(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("k");
    assert(node);
    assert(btree_lookup_1(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("a");
    assert(node);
    assert(btree_lookup_1(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("d");
    assert(node);
    assert(btree_lookup_2(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("g");
    assert(node);
    assert(btree_lookup_2(root, node->name) == NULL);
    root = btree_insert(root, node);

    node = node_create("l");
    assert(node);
    assert(btree_lookup_2(root, node->name) == NULL);
    root = btree_insert(root, node);

    btree_apply_pre(root, node_print, "%s ");
    printf("\n");

    btree_apply_in(root, node_print, "%s ");
    printf("\n");

    btree_apply_post(root, node_print, "%s ");
    printf("\n");

    {
        FILE *f = fopen("test.gv", "w");

        assert(f);

        btree_export_to_dot(f, "test_tree", root);

        fclose(f);
    }

    btree_apply_post(root, node_free, NULL);

    return 0;
}
