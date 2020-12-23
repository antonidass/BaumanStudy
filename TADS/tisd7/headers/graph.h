#include "constants.h"



#ifndef GRAPH_T
#define GRAPH_T

typedef struct adj_node adj_node_t;
struct adj_node
{
    int vertex;
    adj_node_t *next;
};

typedef struct
{
    adj_node_t **adj_matrix;
    int size;
    int *visited;
} graph_t;


adj_node_t *allocate_adj_node(int vertex);

void free_adj_node(adj_node_t **adj_node);

void push_back(adj_node_t **adj_node, int vertex);

void print_nodes(const adj_node_t *head);




#endif