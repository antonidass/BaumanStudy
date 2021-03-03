#include "constants.h"
#include "graph.h"

#ifndef DOT
#define DOT

typedef void (*ptr_action_t)(adj_node_t **, void*, int);

void out_graph_dot(const graph_t *graph, char *name);


void create_path_dot(graph_t *graph, int new_path[], int size_new_path);
#endif