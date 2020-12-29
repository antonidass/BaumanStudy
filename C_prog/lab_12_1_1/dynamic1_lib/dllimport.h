
__declspec(dllimport) int __cdecl key(int *pb_src, int *pe_src, edges_t *edges);

__declspec(dllimport) int __cdecl find_amount_of_elems(FILE *input_data);

__declspec(dllimport) int * __cdecl read_data(FILE *input_data, int *pb_src);

__declspec(dllimport) void __cdecl write_data(FILE *output_data, int *pb, int *pe);

__declspec(dllimport) int __cdecl comp(const void *first, const void *second);

__declspec(dllimport) void __cdecl mysort(void *pb, int total_elems, int size, comp_function_t *comp_function);

__declspec(dllimport) void __cdecl filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst);

__declspec(dllimport) int __cdecl mem_alloc(int **pb, int size);

__declspec(dllimport) void __cdecl mem_dealloc(int **p);

__declspec(dllimport) int __cdecl print_error(int error, FILE *stream);

__declspec(dllimport) int __cdecl parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter);
