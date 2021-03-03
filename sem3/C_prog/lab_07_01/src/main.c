#include "../inc/iostream.h"
#include "../inc/functions.h"


int main(int argc, char *argv[])
{
    char input_file_name[MAX_FILE_NAME], output_file_name[MAX_FILE_NAME];
    int filter = NO;

    int check_args = parse_args(argc, argv, input_file_name, output_file_name, &filter);

    if (check_args != OK)
        return check_args;
        
    FILE *input_data = fopen(input_file_name, "r");

    if (input_data == NULL)
    {
        fprintf(stderr, ERROR_IN_OPEN_FILE_MSG);
        return ERROR_IN_OPEN_FILE;   
    }

    int amount_of_elems = find_amount_of_elems(input_data);

    if (amount_of_elems == 0)
    {
        fprintf(stderr, EMPTY_DATA_ERROR_MSG);
        return EMPTY_DATA_ERROR;
    }

    if (amount_of_elems == ERROR_IN_INPUT_DATA)
    {
        fprintf(stderr, ERROR_IN_INPUT_DATA_MSG);
        return ERROR_IN_INPUT_DATA;
    }

    int *pb_src = NULL;

    int rc = mem_alloc(&pb_src, amount_of_elems);

    if (rc != OK)
    {
        fprintf(stderr, ERROR_IN_MALLOC_MSG);
        return ERROR_IN_MALLOC;
    }
    
    fseek(input_data, 0L, SEEK_SET);

    int *pe_src = read_data(input_data, pb_src);

    LOG_DEBUG("pb = %d   pe = %d   pe - 1 = %d", *pb_src, *pe_src, *(pe_src - 1));
    

    if (filter)
    {
        int *pb_dst = NULL, *pe_dst = NULL;

        int res = key(pb_src, pe_src, &pb_dst, &pe_dst);

        if (print_error(res, stderr) != OK)
        {
            mem_dealloc(&pb_dst);
            mem_dealloc(&pb_src);        
            return res;
        }

        mysort(pb_dst, (int)(pe_dst - pb_dst), sizeof(int), comp);
        
        FILE *output_data = fopen(output_file_name, "w");

        if (output_data == NULL)
        {
            mem_dealloc(&pb_dst);
            mem_dealloc(&pb_src);
            fprintf(stderr, ERROR_IN_OPEN_FILE_MSG);
            return ERROR_IN_OPEN_FILE;
        }

        write_data(output_data, pb_dst, pe_dst);

        mem_dealloc(&pb_dst);
        mem_dealloc(&pb_src);

        if (fclose(output_data) == EOF || fclose(input_data) == EOF)
        {
            fprintf(stderr, ERROR_IN_CLOSING_FILE_MSG);
            return ERROR_IN_CLOSING_FILE;
        }

        return OK;
    }
   
    mysort(pb_src, (int)(pe_src - pb_src), sizeof(int), comp);
    LOG_DEBUG("pb = %d   pe = %d   pe - 1 = %d", *pb_src, *pe_src, *(pe_src - 1));

    FILE *output_data = fopen(output_file_name, "w");

    if (output_data == NULL)
    {
        mem_dealloc(&pb_src);
        fprintf(stderr, ERROR_IN_OPEN_FILE_MSG);
        return ERROR_IN_OPEN_FILE;
    }

    write_data(output_data, pb_src, pe_src);

    mem_dealloc(&pb_src);

    if (fclose(output_data) == EOF || fclose(input_data) == EOF)
    {
        fprintf(stderr, ERROR_IN_CLOSING_FILE_MSG);
        return ERROR_IN_CLOSING_FILE;
    }

    return OK;
}
