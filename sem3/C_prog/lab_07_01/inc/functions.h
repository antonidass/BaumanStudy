#include "constants.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
const int *find_index_max_elem(const int *pb_src, const int *pe_src);
const int *find_index_min_elem(const int *pb_src, const int *pe_src);
int comp(void *first, void *second);
void print_array(int *pb, int total_elems);
char *binary_search(char *copy_pb, char *item_p, char *l, char *r, int size, comp_function_t comp_function);
void mysort(void *pb, int total_elems, int size, comp_function_t *comp_function);
void filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst);
void remember_elem(char *src_byte, const char *dst_byte, int size);
int mem_alloc(int **pb, int size);
void mem_dealloc(int **p);
int print_error(int error, FILE *stream);
int parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter);