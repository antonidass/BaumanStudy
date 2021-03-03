#include "../headers/constants.h"
#include "../headers/info.h"
#include "../headers/common_functions.h"
#include "../headers/graph.h"
#include "../headers/iostream.h"
#include "../headers/dot.h"

extern int path[100];


int main()
{    
    graph_t graph;

    int rc = input_graph_from_file(&graph);

    if (rc != OK)
        return rc;

    int max_path = 0, cur_path, max_vertex;
    int new_path[100] = { 0 };
    int size_new_path;
    int choice;
    
    while (1)
    {
        print_menu_info();
        
        rc = scanf("%d", &choice);

        if (rc != 1 || choice < 0 || choice > 5)
        {
            printf(ERROR_IN_CHOICE_COMMAND_MSG);
            return ERROR_IN_CHOICE_COMMAND;
        }

        rc = OK;

        switch (choice)
        {
        case 0:
            return OK;
            break;
        case 1:
            rc = input_graph_from_console(&graph);
            break;
        case 2:
            rc = input_graph_from_file(&graph);
            break;
        case 3:
            print_graph(&graph);
            out_graph_dot(&graph, "g.dot");
            system("dot -Tpng g.dot -o g.png");
            break;
        case 4:
            find_max_path(&graph, &max_path, &max_vertex);    
            cur_path = DFS_path(&graph, max_vertex);
            size_new_path = exclude(&graph, new_path,  max_path - 1);
            create_path_dot(&graph, new_path, size_new_path);
            system("dot -Tpng g.dot -o g.png");
            break;

        default:
            break;
        }

        if (rc != OK)
            return rc;
    }

    return OK;
}