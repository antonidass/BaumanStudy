#include "../headers/dot.h"


void graph_apply(const graph_t *graph, ptr_action_t f, void *arg)
{
    f(graph->adj_matrix, arg, graph->size);
}


void graph_to_dot(adj_node_t **matrix, void *param, int size)
{
    FILE *f = param;

    if (!matrix)
        return;



    for (int i = 0; i < size; i++)
    {
        adj_node_t *temp = matrix[i];
        while (temp)
        {
            if (temp->vertex > i)
                fprintf(f, "%d -- %d;\n", i + 1, temp->vertex);
                
            temp = temp->next;
        }
    }
}


void graph_export_to_dot(FILE *f, const char *graph_name, const graph_t *graph)
{
    fprintf(f, "graph %s {\n", graph_name);
    graph_apply(graph, graph_to_dot, f);
    fprintf(f, "}\n");
}


void out_graph_dot(const graph_t *graph, char *name)
{
    FILE *f = fopen(name, "w");
    graph_export_to_dot(f, "g", graph);
    fclose(f);
}


int in_new_path(int new_path[], int size, int vertex)
{
    for (int i = 0; i < size; i++)
    {
        if (new_path[i] == vertex)
            return 1;
    }

    return 0;
}





void create_path_dot(graph_t *graph, int new_path[], int size_new_path)
{
    FILE *f = fopen("g.dot", "w");

    fprintf(f, "graph %s {\n", "g");



    for (int i = 0; i < graph->size; i++)
    {
        adj_node_t *temp = graph->adj_matrix[i];
        while (temp)
        {
           
            if (temp->vertex > i && in_new_path(new_path, size_new_path, i + 1) && in_new_path(new_path, size_new_path, temp->vertex))
            {
                fprintf(f, "%d -- %d [weight=12, color=red, style=filled];\n", i + 1, temp->vertex);
            }
            else if (temp->vertex > i )
            {
                fprintf(f, "%d -- %d;\n", i + 1, temp->vertex);
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < size_new_path; i++)
    {
        fprintf(f, "%d [color=maroon, style=filled];\n", new_path[i]);
    }


    fprintf(f, "}\n");



    fclose(f);



    printf("\n\nСамый длинный простой путь в графе : ");

    for (int i = 0; i < size_new_path - 1; i++)
    {
        printf("%d -- ", new_path[i]);
    }

    printf("%d\n", new_path[size_new_path - 1]);
}   

