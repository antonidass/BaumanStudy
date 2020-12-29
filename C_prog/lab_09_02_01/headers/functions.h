#include "constants.h"


int compare(const void *x1, const void *x2);
int find_substring_words(object_t objects[], int n, char substring[], object_t substring_objects[]);
int check_data(const double *first, const double *second);
int parse_args(int argc, char **argv, char **input_file_name, char **substr);
int mem_alloc(object_t **pb, int count_elems, int size_object);
void mem_dealloc(object_t **p, int n);
void free_args(char **input_file_name, char **substr);