#include "../headers/iostream.h"



int read_data(tree_node_t **tree, int type)
{
    FILE *file;

    if (type == 1)
        file = fopen("data.txt", "r");
    else
        file = fopen("data2.txt", "r");
    

    
    int rc;
    char temp_str[MAX_LEN_LINE];
    int i = 0;
    
    while (!feof(file))
    {
        rc = fscanf(file, "%s", temp_str);

        if (rc != 1)
        {
            printf(ERROR_IN_INPUT_DATA_MSG, i + 1);
            return ERROR_IN_INPUT_DATA;
        }

        tree_node_t *node = node_create(temp_str);

        if (!node)
            return ERROR_IN_MALLOC;
        *tree = btree_insert(*tree, node);

        i++;
    }   

    fclose(file);

    return i;
}


void print_btree(const tree_node_t *tree, int ident)
{
    if (tree)
    {
        print_btree(tree->right, ident + 4);
        
        for (int i = 0; i < ident; i++)
            printf(" ");

        if (tree->data)
            printf("%s\n", tree->data);

        print_btree(tree->left, ident + 4);
    }
}




void print_menu_info()
{
    printf("\n\nПрограмма предназначена для хранения и обработки данных с помощью ДДП, АВЛ дерева и хеш-таблицы.\n"
            "Также программа позволяет вывести время и объем занимаемой памяти при хранении данных в виде ДДП, АВЛ, хеш-таблицы и файла.\n"
            "Для вывода деревьев используется Graphviz\n\n"
           "0 - Выход из программы\n"
           "1 - Вывод данных из файла в виде бинарного дерева\n"
           "2 - Вывод данных из файла в виде сбалансированного бинарного дерева\n"
           "3 - Вывод данных из файла в виде хеш-таблицы\n"
           "4 - Удаление указанного слова\n"
           "5 - Сравнение операции удаления по времени и по памяти. Вывод среднего количества сравнений\n"
            );

    printf("Выберите пункт : ");
}