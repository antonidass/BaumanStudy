#include "my_functions.h"


int create_bin_file(char *n_str, char *file_name)
{
    int n = atoi(n_str);
    size_t wrote;

    FILE *file = fopen(file_name, "wb");

    if (file == NULL)
        return FILE_NAME_ERR;

    for (int i = 0; i < n; i++)
    {
        int num = rand() % 100;
    
        wrote = fwrite(&num, sizeof(int), 1, file);

        if (wrote != 1)
            return WRITE_DATA_ERR;            
    }

    fclose(file);

    return OK;
}


int file_size(FILE *file, size_t *size)
{
    fseek(file, 0L, SEEK_END);

    *size = (size_t)(ftell(file)) / sizeof(int);

    if (*size == 0)
        return SIZE_ERR;

    fseek(file, 0L, SEEK_SET);

    return OK;
}

int print_bin_file(char *file_name)
{
    FILE *file = fopen(file_name, "rb");

    if (file == NULL)
        return FILE_NAME_ERR;

    size_t size;
    int num;

    if (!file_size(file, &size))
    {
        for (size_t i = 0; i < size; i++)
        {
            fread(&num, sizeof(int), ONE_ELEMENT, file);
            printf("%d ", num);
        }   
    }
    else
        return SIZE_ERR;

    fclose(file);

    return OK;
}


int get_number_by_pos(FILE *file, size_t pos)
{
    int temp_num;

    fseek(file, pos * sizeof(int), SEEK_SET);
    fread(&temp_num, sizeof(int), ONE_ELEMENT, file);

    return temp_num;
}

void put_number_by_pos(FILE *file, size_t pos, int *temp_num)
{
    fseek(file, pos * sizeof(int), SEEK_SET);
    fwrite(temp_num, sizeof(int), ONE_ELEMENT, file);
}


int sort_bin_file(char *file_name)
{
    FILE *file = fopen(file_name, "rb+");

    if (file == NULL)
        return FILE_NAME_ERR;

    size_t size;
    int first_num, second_num;

    if (file_size(file, &size))
        return READ_FILE_ERR;

    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            first_num = get_number_by_pos(file, j);
            second_num = get_number_by_pos(file, j + 1);

            if (first_num > second_num)
            {
                put_number_by_pos(file, j, &second_num);
                put_number_by_pos(file, j + 1, &first_num);
            }
        }
    }
    
    fclose(file);

    return OK;
}