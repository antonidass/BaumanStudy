#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INITIAL_VALUE 2
#define WRITE_DATA_ERR -1
#define LAUNCH_PARAMETERS_ERR -2
#define SIZE_ERR 1
#define FILE_NAME_ERR -3
#define READ_FILE_ERR -4
#define ONE_ELEMENT 1

#define LAUNCH_PARAMS_MSG "Error in launch params"
#define ARGS_MSG "Error in args"
#define INPUT_DATA_MSG "Error in input data"
#define SIZE_MSG "Error in file size"
#define FILE_NAME_MSG "Error in file name"
#define READ_FILE_MSG "Error in read file"


int create_bin_file(char *n_str, char *file_name);
int print_bin_file(char *file_name);
int sort_bin_file(char *file_name);
void put_number_by_pos(FILE *file, size_t pos, int *temp_num);
int get_number_by_pos(FILE *file, size_t pos);
int file_size(FILE *file, size_t *size); 