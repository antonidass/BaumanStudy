#include "../headers/common_functions.h"


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



int delete_data(tree_node_t **tree_root, tree_node_t **balance_tree_root, list_t ***table, int *size_table)
{
    printf("Введите удаляемое слово: ");
    char temp_str[MAX_LEN_LINE];
    int rc = scanf("%s", temp_str);

    if (rc != 1)
    {
        printf("Ошибка. Указанного слова не существует\n");
        return NOT_EXIST_ERROR;
    }

    int depth = search_tree(temp_str, **tree_root);

    if (depth == NOT_FOUND)
    {
        printf("Ошибка. Указанного слова не существует\n");
        return NOT_EXIST_ERROR;
    }


    *tree_root = delete_node(*tree_root, temp_str);

    // char *nu = "NULL";
    // printf("node.data %s", node ? node->data : nu);


    *balance_tree_root =  delete_node(*balance_tree_root, temp_str);
    
    int count_len;
    tree_node_t *new_balance = balance_tree(*balance_tree_root, &count_len);

    *balance_tree_root = new_balance;


    delete_data_htable(table, size_table, temp_str, -1);


    printf("\n Слово успешно удалено !!!\n");

    return OK;
}


void make_file(int size)
{
    FILE *file = fopen("data2.txt", "w");

    srand(time(0));

    char temp_str[MAX_LEN_LINE];

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            temp_str[i] = (char) (rand() % 20  + 60);

        }
        temp_str[5] = '\0';
        // printf("%s\n", temp_str);

        if (k == size -1)
            fprintf(file, "%s", temp_str);
        else
            fprintf(file, "%s\n", temp_str);
    }

    fclose(file);
}



void get_random_word(char *word, int size)
{
    FILE *file = fopen("data2.txt", "r");

    int random = rand() % size;

    for (int i = 0; i < random; i++)
    {
        fscanf(file, "%s", word);
    }

    fclose(file);

    // printf("random = %d\n", random);
    // printf("random word = %s\n\n", word);
}



uint64_t find_in_file(int k)
{
    FILE *file = fopen("data2.txt", "r");

    char temp[MAX_LEN_LINE];

    uint64_t start = tick();
    for (int i = 0; i < k; i++)
    {
        fscanf(file, "%s", temp);
    }

    uint64_t end = tick();

    fclose(file);

    return end - start;
}



int comparison_delete()
{
    int size;
    printf("Введите колиство строк в файле: ");
    int rc = scanf("%d", &size);

    if (rc != 1 || size <= 0)
    {
        printf("Неверный размер файла !\n");
        return ERROR_IN_MALLOC;
    }

    make_file(size);

    int ddp_comp;
    list_t **table = NULL;
    int max_collisions;


    tree_node_t *root = NULL;

    int count_lines = read_data(&root, 2);
    int lines;

    // printf("%d")

    tree_node_t *balanced_root = balance_tree(root, &lines);
       
    root = NULL;
    count_lines = read_data(&root, 2);


    int size_table = size * 10;
    build_hash_table(&table, &size_table, 2);

    char random_word[MAX_LEN_LINE];

    get_random_word(random_word, size);

    char word[MAX_LEN_LINE];
    strcpy(word, random_word);


    // printf("%s WORD \n\n", word);


    // print_btree(balanced_root, 4);
    // print_btree(root, 4);
    // printf("random word=  %s\n\n", random_word);
    // printf("\n%s\n", random_word);

    uint64_t sum_time, start, stop;

    start = tick();
    delete_node(root, word);
    stop = tick();

    printf("Время измеряется в тактах !\n");
    sum_time = stop - start;
    printf("\n\nВремя удаления в ДДП дереве = %lu\n", sum_time);
    
    strcpy(word, random_word);

    // printf("%s WORD \n\n", word);

    start = tick();
    delete_node(balanced_root, word);
    stop = tick();

    sum_time = stop - start;
    printf("Время удаления в АВЛ дереве = %lu\n", sum_time);

    strcpy(word, random_word);

    // print_hash_table(table, size_table);
    get_random_word(random_word, size);
    // printf("%s random word \n\n", random_word);
    // printf("size_table =%d size_table = %d\n\n", size, size_table);

    int key = hash_func(word, size_table);

    start = tick();
    delete_data_htable(&table, &size_table, word, key);
    stop = tick();

    sum_time = stop - start;

    printf("Время удаления в хеш-таблице = %lu\n", sum_time);

    printf("Время удаления в файле = %lu\n\n", find_in_file(size / 5));
    
    printf("Объем занимаемой памяти. Измеряется в байтах. \n");
    printf("ДДП -  %d\n", size * (24));
    printf("АВЛ -  %d\n", size * (24));
    printf("Хеш-таблица -  %d\n", 8 + size * 16);
    printf("Файл -  %d\n\n", 6 * size);
    

    printf("Среднее количество сравнений (без коллизий) \n");
    printf("ДДП - %d\n", (int)   (log2((double)size) + log2((double)size)));
    printf("АВЛ - %d\n", (int)log2((double)size));
    printf("Хеш-таблица - %d\n", 1);
    printf("Файл - %d\n\n", size / 2);
   
    return OK;
}