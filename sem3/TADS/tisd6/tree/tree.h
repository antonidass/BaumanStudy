#ifndef __BIN_TREE_H__

#define __BIN_TREE_H__


#include <stdio.h>
#include "tree_node.h"


typedef void (*ptr_action_t)(struct tree_node_t*, void*);


struct tree_node_t* btree_insert(struct tree_node_t *tree, struct tree_node_t *node);


struct tree_node_t* btree_lookup_1(struct tree_node_t *tree, const char *name);


struct tree_node_t* btree_lookup_2(struct tree_node_t *tree, const char *name);


void btree_apply_pre(struct tree_node_t *tree, ptr_action_t f, void *arg);


void btree_apply_in(struct tree_node_t *tree, ptr_action_t f, void *arg);


void btree_apply_post(struct tree_node_t *tree, ptr_action_t f, void *arg);


void btree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree);


#endif	// #ifndef __BIN_TREE_H__
