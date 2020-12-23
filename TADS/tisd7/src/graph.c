#include "../headers/graph.h"


adj_node_t *allocate_adj_node(int vertex)
{
    adj_node_t *new = malloc(sizeof(adj_node_t));

    new->vertex = vertex;
    new->next = NULL;

    return new;
}


void free_adj_node(adj_node_t **adj_node)
{
    if (*adj_node)
        free(*adj_node);
}


adj_node_t *get_last_node(adj_node_t *head)
{
    if (!head)
        return NULL;

    while (head->next)
        head = head->next;
    
    return head;
}


void push_back(adj_node_t **adj_node, int vertex)
{
    adj_node_t *new = allocate_adj_node(vertex);

    if (!*adj_node)
    {
        *adj_node = new;
    }
    else
    {
        adj_node_t *last = get_last_node(*adj_node);
        last->next = new;
    }
}


void print_nodes(const adj_node_t *head)
{
    while (head)
    {
        printf("%d ", head->vertex);
        head = head->next;
    }
}


void create_graph(graph_t *graph, int size)
{
    graph->size = size;
    graph->adj_matrix = malloc(size * sizeof(adj_node_t *));
    graph->visited = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        graph->adj_matrix[i] = NULL;
        graph->visited[i] = 0;
    }
}