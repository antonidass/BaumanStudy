#include "constants.h"


int key(int *pb_src, int *pe_src, edges_t *edges);

int *find_index_max_elem(int *pb_src, int *pe_src);

int *find_index_min_elem(int *pb_src, int *pe_src);

int comp(const void *first, const void *second);

void print_array(int *pb, int total_elems);

char *binary_search(char *copy_pb, char *item_p, char *l, char *r, int size, comp_function_t comp_function);

void mysort(void *pb, int total_elems, int size, comp_function_t *comp_function);


void filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst);

void remember_elem(char *src_byte, char *dst_byte, int size);

int mem_alloc(int **pb, int size);

void mem_dealloc(int **p);

int print_error(int error, FILE *stream);

int parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter);