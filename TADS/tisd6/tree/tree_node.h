#ifndef __TREE_NODE_H__

#define __TREE_NODE_H__


struct tree_node_t
{
    const char *name;

    // �������
    struct tree_node_t *left;
    // �������
    struct tree_node_t *right;
};


struct tree_node_t* node_create(const char *name);


void node_print(struct tree_node_t *node, void *param);


void node_free(struct tree_node_t *node, void *param);


void node_to_dot(struct tree_node_t *tree, void *param);


#endif	// #ifndef __TREE_NODE_H__