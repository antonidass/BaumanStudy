#include "../headers/iostream.h"




int input_graph_from_file(graph_t *graph)
{
    FILE *file = fopen("data.txt", "r");

    int i = 0, vertex, rc, size;

    rc = fscanf(file, "%d", &size);

    if (rc != 1 || size <= 0)
    {
        return ERROR_IN_SIZE_GRAPH;
    }

    create_graph(graph, size);

    while (!feof(file) && i < size)
    {
        rc = fscanf(file, "%d", &vertex);

        if (rc != 1 || vertex <= 0 || vertex > size)
        {
            printf("Ошибка в размере графа\n");
            return ERROR_IN_INPUT_DATA;
        }

        int count;
        rc = fscanf(file, "%d", &count);

        if (rc != 1 || count > size || count <= 0)
        {
            printf("Ошибка в количестве вершин\n");
            return ERROR_IN_VERTEX;
        }
        
        int ver;
        for (int j = 0; j < count; j++)
        {
            rc = fscanf(file, "%d", &ver);

            if (rc != 1 || ver > size || ver <= 0)
            {
                printf("Введена неверная вершина\n");
                return ERROR_IN_VERTEX;
            }

            push_back(&graph->adj_matrix[i], ver);
        }

        i++;
    }

    fclose(file);

    return OK; 
}


void print_graph(const graph_t *graph)
{
    printf("\n\nПредставление графа в виде списка смежности :\n");
    for (int i = 0; i < graph->size; i++)
    {
        printf("Вершина №%d  : ", i + 1);
        print_nodes(graph->adj_matrix[i]);
        printf("\n");
    }
}



int input_graph_from_console(graph_t *graph)
{
    printf("Введите количество вершин графа : ");
    int size_graph;
    int rc = scanf("%d", &size_graph);
    printf("\n");

    if (rc != 1 || size_graph <= 0)
    {
        printf("Неверное количество вершин графа !!\n");
        return ERROR_IN_SIZE_GRAPH;
    }

    create_graph(graph, size_graph);


    int count;
    for (int i = 0; i < graph->size; i++)
    {
        printf("Введите количество связей вершины %d :  ", i+1);
        rc = scanf("%d", &count);

        if (rc != 1 || count < 0 || count >= graph->size)
        {
            printf("Неверное количество связей!\n");
            return ERROR_IN_COUNT_RELATIONS;
        }

        int vertex;
        printf("Укажите в порядке возрастания вершины (%d) с которыми связана вершина %d через пробел : ", count,  i+1);
        for (int j = 0; j < count; j++)
        {
            rc = scanf("%d", &vertex);

            if (rc != 1 || vertex == i + 1 || vertex <= 0 || vertex > graph->size)
            {
                printf("Указана неверная вершина!\n");
                return ERROR_IN_VERTEX;
            }

            push_back(&graph->adj_matrix[i], vertex);
            
        }

    }

    return OK;
}