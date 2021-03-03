#include "iostream.h"



__declspec(dllexport) int __cdecl find_amount_of_elems(FILE *input_data)
{
    int amount = 0;
    int temp_num, rc;

    while ((rc = fscanf(input_data, "%d", &temp_num)) != EOF)
    {
        if (rc != 1)
            return ERROR_IN_INPUT_DATA;
        LOG_DEBUG("%d ", temp_num);
        amount++;
    }

    return amount;
}


__declspec(dllexport) int * __cdecl read_data(FILE *input_data, int *pb_src)
{
    while (fscanf(input_data, "%d", (pb_src++)) != EOF) ;

    LOG_DEBUG("%d ", *(pb_src + i-1));
    return --pb_src;
}


__declspec(dllexport) void __cdecl write_data(FILE *output_data, int *pb, int *pe)
{
    while (pb != pe)
    {
        LOG_DEBUG("pb = %p    *pb = %d", (void*)pb, *pb);
        fprintf(output_data, "%d ", *pb);
        pb++;
    }
}