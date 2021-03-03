#include "constants.h"
#include "graph.h"


int DFS(graph_t *graph, int vertex);

int DFS_path(graph_t *graph, int vertex);

int exclude(graph_t *graph, int new_path[], int max_path);

void find_max_path(graph_t *graph, int *max_path, int *max_vertex);

int input_graph_from_console(graph_t *graph);

uint64_t tick(void);