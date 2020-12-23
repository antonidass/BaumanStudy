#include "constants.h"
#include "binary_tree.h"
#include "list.h"

#ifndef HASH
#define HASH


typedef struct 
{
    tree_node_t **arr;
    int size;
    int mem_size;
} arr_t;


typedef int (*hash_func_t)(char *, int);

int is_prime(int num);



void print_hash_table(list_t **arr, int size);

void delete_data_htable(list_t ***table, int *size_table, char *data, int key_word);

int build_hash_table(list_t ***table, int *size, int type);


#endif