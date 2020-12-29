#include "functions.h"


int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
        return AMOUNT_PARAMS_ERR;

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
        return FILE_NAME_ERR;

    object_t objects[MAX_OBJECTS];
    int n = read_objects(file, objects);
    
    if (fclose(file) == EOF)
        return FILE_CLOSE_ERR;

    if (n < 0)
        return n;

    if (argc == 2)
    {
        qsort(objects, n, sizeof(objects[0]), compare);
        print_objects(objects, n);
    }
    else if (!strcmp(argv[2], "ALL"))
    {
        print_objects(objects, n);
    }
    else
    {
        object_t substrings_objects[MAX_OBJECTS];
        int count_substring_objects = find_substring_words(objects, n, argv[2], substrings_objects);

        if (count_substring_objects == 0)
            return ZERO_SUBSTRING_OBJECTS_ERR;

        print_objects(substrings_objects, count_substring_objects);
    }
    return OK;
}