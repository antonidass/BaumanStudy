#include "constants.h"
#include "binary_tree.h"
#include "list.h"
#include "hash.h"
#include "balance_tree.h"
#include "iostream.h"
#include "dot.h"


uint64_t tick(void);

int delete_data(tree_node_t **tree_root, tree_node_t **balance_tree_root, list_t ***table, int *size_table);

void make_file(int size);

void get_random_word(char *word, int size);

int comparison_delete();

int hash_func(char *data, int size_table);