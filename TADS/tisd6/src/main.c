#include "../headers/constants.h"
#include "../headers/iostream.h"
#include "../headers/binary_tree.h"
#include "../headers/balance_tree.h"
#include "../headers/dot.h"
#include "../headers/hash.h"
#include "../headers/common_functions.h"



int main()
{
    list_t **table = NULL;
    int size_table = 0;
    int max_collisions;


    int rc, choice = -1;
    FILE *file = fopen("data.txt", "r");

    tree_node_t *root = NULL;
    int count_lines = read_data(&root, 1);
    int lines;

    if (count_lines <= 0)
        return count_lines;

    rewind(file);


    tree_node_t *balanced_root = balance_tree(root, &lines);
       
    root = NULL;
    count_lines = read_data(&root, 1);

    out_btree_dot(root, "tree.gv");
    out_btree_dot(balanced_root, "balanced_tree.gv");

    fclose(file);


    

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
            print_btree(root, 4);
            out_btree_dot(root, "tree.gv");
            break;
        case 2:
            print_btree(balanced_root, 4);
            out_btree_dot(balanced_root, "balanced_tree.gv");
            break;
        case 3:
            if (table == NULL)
            {
                max_collisions = build_hash_table(&table, &size_table, 1);

                if (max_collisions < 0)
                    return max_collisions;
            }
            print_hash_table(table, size_table);
            break;
        case 4:
            if (table == NULL)
            {
                printf("Сначала введите размер таблицы!\n");
                break;
            }
            rc = delete_data(&root, &balanced_root, &table, &size_table);
            break;
        case 5:
            rc = comparison_delete();
            break;

        default:
            break;
        }

        if (rc != OK)
            return rc;
    }






    return OK;
}