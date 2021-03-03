#include "../headers/iostream.h"



int main(int argc, char **argv)
{
    char *substr = NULL, *file_name = NULL;
    
    int check_args = parse_args(argc, argv, &file_name, &substr);

    if (check_args != OK)
    {
        free_args(&file_name, &substr);
        return check_args;
    }

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        free_args(&file_name, &substr);
        return FILE_NAME_ERR;
    }

    int count = count_elems(file);

    if (count <= 0)
    {
        fclose(file);
        free_args(&file_name, &substr);
        return count;
    }

    

    int object_amount = count / OBJECT_FIELD_AMOUNT;
    object_t *objects = NULL;
    LOG_DEBUG("size = %lu", sizeof(object_t));

    int rc = mem_alloc(&objects, object_amount, sizeof(object_t));

    if (rc != OK)
    {
        free_args(&file_name, &substr);
        return rc;
    }

    rewind(file);
    rc = read_objects(file, objects);

    if (fclose(file) == EOF)
    {
        free_args(&file_name, &substr);
        mem_dealloc(&objects, object_amount);
        return FILE_CLOSE_ERR;
    }
    if (rc != OK)
    {
        free_args(&file_name, &substr);
        mem_dealloc(&objects, object_amount);
        return rc;
    }

    if (!substr)
    {
        qsort(objects, object_amount, sizeof(objects[0]), compare);
        print_objects(objects, object_amount);
    }
    else if (!strcmp(substr, "ALL"))
    {
        print_objects(objects, object_amount);
    }
    else
    {
        object_t *substrings_objects = NULL;
        rc = mem_alloc(&substrings_objects, object_amount, sizeof(object_t));

        if (rc != OK)
        {
            free_args(&file_name, &substr);
            mem_dealloc(&objects, object_amount);
            return rc;
        }

        int count_substring_objects = find_substring_words(objects, object_amount, substr, substrings_objects);

        if (count_substring_objects == 0)
        {
            free_args(&file_name, &substr);
            mem_dealloc(&substrings_objects, 0);
            mem_dealloc(&objects, object_amount);
            return ZERO_SUBSTRING_OBJECTS_ERR;
        }

        print_objects(substrings_objects, count_substring_objects);
        mem_dealloc(&substrings_objects, 0);
    }

    mem_dealloc(&objects, object_amount);
    free_args(&file_name, &substr);

    return OK;
}