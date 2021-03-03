#include "constants.h"


__declspec(dllexport) int __cdecl find_amount_of_elems(FILE *input_data);

__declspec(dllexport) int * __cdecl read_data(FILE *input_data, int *pb_src);

__declspec(dllexport) void __cdecl write_data(FILE *output_data, int *pb, int *pe);
