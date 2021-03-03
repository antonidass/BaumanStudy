#include "constants.h"


__declspec(dllexport) int __cdecl key(int *pb_src, int *pe_src, edges_t *edges);

int *find_index_max_elem(int *pb_src, int *pe_src);

int *find_index_min_elem(int *pb_src, int *pe_src);

__declspec(dllexport) int __cdecl comp(const void *first, const void *second);

char *binary_search(char *copy_pb, char *item_p, char *l, char *r, int size, comp_function_t comp_function);

__declspec(dllexport) void __cdecl mysort(void *pb, int total_elems, int size, comp_function_t *comp_function);


__declspec(dllexport) void __cdecl filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst);

void remember_elem(char *src_byte, char *dst_byte, int size);

__declspec(dllexport) int __cdecl mem_alloc(int **pb, int size);

__declspec(dllexport) void __cdecl mem_dealloc(int **p);

__declspec(dllexport) int __cdecl print_error(int error, FILE *stream);

__declspec(dllexport) int __cdecl parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter);