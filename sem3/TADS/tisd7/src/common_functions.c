#include "../headers/common_functions.h"



extern int path[100];



int DFS(graph_t *graph, int vertex)
{
    adj_node_t *adj_list = graph->adj_matrix[vertex - 1];
    adj_node_t *temp = adj_list;

    graph->visited[vertex - 1] = 1; 

    int max_depth = 0;
    int temp_depth = 0;

    while (temp)
    {
        int connected_vertex = temp->vertex;

        if (graph->visited[connected_vertex - 1] == 0)
        {
            temp_depth = DFS(graph, connected_vertex);

            if (temp_depth > max_depth)
                max_depth = temp_depth;
        }

        temp = temp->next;
    }


    return max_depth + 1;
}


int DFS_path(graph_t *graph, int vertex)
{
    adj_node_t *adj_list = graph->adj_matrix[vertex - 1];
    adj_node_t *temp = adj_list;

    graph->visited[vertex - 1] = 1; 

    int max_depth = 0;
    int temp_depth = 0;

    while (temp)
    {
        int connected_vertex = temp->vertex;

        if (graph->visited[connected_vertex - 1] == 0)
        {
            temp_depth = DFS_path(graph, connected_vertex);

            if (temp_depth > max_depth)
                max_depth = temp_depth;
        }

        temp = temp->next;
    }

    path[vertex - 1] = max_depth;
    return max_depth + 1;
}



int exclude(graph_t *graph, int new_path[], int max_path)
{
    int count;
    int max_vertexes[100] = {0};
    int new_path_i = 0;

    // Узнаем индекс первого максиума в path 
    int vertex_first_max;
    int first = 1;
    for (int i = 0; i < graph->size; i++)
    {
        if (path[i] == max_path && first)
        {
            vertex_first_max = i;
            first = 0;
        }
        else if (path[i] == max_path)
        {
            path[i] = -1;
        }
    }
    max_path--;


    new_path[new_path_i++] = vertex_first_max + 1;

    while (max_path >= 0)
    {
        adj_node_t *temp = graph->adj_matrix[vertex_first_max];
    
        while (temp)
        {
            if (path[temp->vertex - 1] == max_path)
            {
                new_path[new_path_i++] = temp->vertex;
                vertex_first_max = temp->vertex - 1;
                break;
            }

            temp = temp->next;
        }

        max_path--;
    }
    
    return new_path_i;
}




void find_max_path(graph_t *graph, int *max_path, int *max_vertex)
{
    int cur_path;

    for (int i = 0; i < graph->size; i++)
    {
        cur_path = DFS(graph, i + 1);

        for (int j = 0; j < graph->size; j++)
        {
            graph->visited[j] = 0;
        }

        if (cur_path > *max_path)
        {
            *max_vertex = i + 1;
            *max_path = cur_path;
        }
    }

}



uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
