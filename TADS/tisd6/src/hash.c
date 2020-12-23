#include "../headers/hash.h"


int is_prime(int num)
{
    if (num <= 1)
        return 0;

    if (num % 2 == 0 && num > 2)
        return 0;

    for (int i = 3; i <= floor(sqrt(num)); i += 2)
        if (num % i == 0)
            return 0;
    
    return 1;
}



int get_prime(int size_table)
{
    int prime_num = size_table;

    while ((prime_num > 2) && !is_prime(prime_num))
        prime_num--;
    
    // printf("prime = %d\n", prime_num);
    return prime_num;
}



int hash_func(char *data, int size_table)
{
    int magic_num = get_prime(size_table);
    int sum = 0;

    int i = 0;
    while (*(data + i) != '\0')
    {
        sum += (int)(*(data + i));
        i++;
    }

    // printf("sum = %d  sum mod magic_num = %d", sum, sum % magic_num);

    return sum % magic_num;
}



int build_hash_table(list_t ***table, int *size, int type)
{
    FILE *f;

    if (type == 1)
        f = fopen("data.txt", "r");
    else
        f = fopen("data2.txt", "r");
        

    int size_table;
    int rc;

    if (type == 1)
    {

        printf("Введите размер таблицы : ");
        rc = scanf("%d", &size_table);

        if (rc != 1 || size_table <= 0)
        {
            printf("Ошибка. Введен неверный размер таблицы!\n");
            return ERROR_IN_TABLE_SIZE;
        }
    } 
    else
    {
        size_table = *size; 
    }
    
    // Создаем таблицу
    *table = malloc(size_table * sizeof(list_t *));

    *size = size_table;
    // Заполняем нулями
    for (int i = 0; i < size_table; i++)
        (*table)[i] = NULL;
    

    char buffer[STR_SIZE];
    int max_collisions = 0;
    int key = 0;
    int z = 0;

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        int cur_collisions = 0;

        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        key = hash_func(buffer, size_table);


        cur_collisions = 1;
        if (!(*table)[key])
        {
            (*table)[key] = malloc(sizeof(list_t));
            (*table)[key]->value = malloc(sizeof(char) * (strlen(buffer) + 1));
            (*table)[key]->next = NULL;
            strcpy(((*table)[key])->value, buffer);
            cur_collisions = 1;
        }

        else
        {
            list_t *temp = (*table)[key];

            while (temp->next)
            {
                cur_collisions++;
                temp = temp->next;
            }

            list_t *new_node = malloc(sizeof(list_t));
            new_node->next = NULL;
            new_node->value = malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(new_node->value, buffer);

            temp->next = new_node;
        }

        if (cur_collisions > max_collisions)
            max_collisions = cur_collisions;
    }


    fclose(f);
    return max_collisions;
}


void print_hash_table(list_t **arr, int size)
{
    printf(
           "\n\n  хеш     | соответствующие данные \n\n");
    list_t *entry;

    for (int i = 0; i < size; i++)
    {
        entry = arr[i];

        if (entry)
            printf("%4d      | ", i);


        while (entry)
        {
            printf("\"%s\" ", entry->value);

            entry = entry->next;

            if (!entry)
                printf("\n");
        }
    }
}



void delete_data_htable(list_t ***table, int *size_table, char *data, int key_word)
{

    int key;

    if (key_word == -1)
        key = hash_func(data, *size_table);
    else
    {
        key = key_word;
    }
    

    int cmp = strcmp((*table)[key]->value, data);

    // printf("data = %s   table key = %s     %d \n\n", data, (*table)[key]->value, cmp);

    if (cmp == 0)
    {
        (*table)[key] = (*table)[key]->next;
    }
    else
    {
        list_t *node = (*table)[key];

        while (node->next && strcmp(node->next->value, data))
        {
            node = node->next;
        }

        if (!node->next)
            return;

        if (node->next->next)
        {
            node->next = node->next->next;
        }
        else
        {
            node->next = NULL;
        }   
    }
}