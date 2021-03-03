#include "constants.h"

#ifdef FUNC_EXPORTS
#define FUNC_DLL __declspec(dllexport)
#else
#define FUNC_DLL __declspec(dllimport)
#endif

#define FUNC_DECL __cdecl



FUNC_DLL int FUNC_DECL key(int *pb_src, int *pe_src, edges_t *edges);

int *find_index_max_elem(int *pb_src, int *pe_src);

int *find_index_min_elem(int *pb_src, int *pe_src);

FUNC_DLL int FUNC_DECL comp(const void *first, const void *second);

char *binary_search(char *copy_pb, char *item_p, char *l, char *r, int size, comp_function_t comp_function);

FUNC_DLL void FUNC_DECL mysort(void *pb, int total_elems, int size, comp_function_t *comp_function);

FUNC_DLL void FUNC_DECL filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst);

void remember_elem(char *src_byte, char *dst_byte, int size);

FUNC_DLL int FUNC_DECL mem_alloc(int **pb, int size);

FUNC_DLL void FUNC_DECL mem_dealloc(int **p);

FUNC_DLL int FUNC_DECL print_error(int error, FILE *stream);

FUNC_DLL int FUNC_DECL parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter);