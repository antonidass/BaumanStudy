#include "constants.h"


#ifdef IO_EXPORTS
#define IO_DLL __declspec(dllexport)
#else
#define IO_DLL __declspec(dllimport)
#endif

#define IO_DECL __cdecl


IO_DLL int IO_DECL find_amount_of_elems(FILE *input_data);

IO_DLL int * IO_DECL read_data(FILE *input_data, int *pb_src);

IO_DLL void IO_DECL write_data(FILE *output_data, int *pb, int *pe);
