#include "../headers/functions.h"



int mem_alloc(object_t **pb, int count_elems, int size_object)
{
    *pb = malloc(count_elems * size_object);

    if (pb == NULL)
        return ERROR_IN_MALLOC;
    
    for (int i = 0; i < count_elems; i++)
        (*pb + i)->name = NULL;

    return OK;
}


void mem_dealloc(object_t **p, int n)
{
    if (*p != NULL)
    {
        for (int i = 0; i < n; i++) 
        {
            if ((*p + i)->name)
                free((*p + i)->name);
        }

        free(*p);
    }
}


int compare(const void *x1, const void *x2)
{
    if ((*(object_t *) x1).density - (*(object_t *) x2).density > EPS)
        return POSITIVE_NUMBER;
    
    if ((*(object_t *) x1).density - (*(object_t *) x2).density > -EPS)
        return ZERO;

    return NEGATIVE_NUMBER;
}


int find_substring_words(object_t objects[], int n, char substring[], object_t substring_objects[])
{
    int count_substring_words = 0;

    for (int i = 0; i < n; i++)
    {
        int j = 0;

        while (substring[j] != '\0' && substring[j] == objects[i].name[j])
            j++;
        
        if (substring[j] == '\0')
            substring_objects[count_substring_words++] = objects[i];
    }
    
    return count_substring_words;
}


int check_data(const double *first, const double *second)
{
    if (*first < EPS || *second < EPS)
        return DATA_ERR;

    return OK;
}



int parse_args(int argc, char **argv, char **input_file_name, char **substr)
{
    if (argc < 2 || argc > 3)
        return AMOUNT_PARAMS_ERR;

    *input_file_name = malloc((strlen(argv[1]) + 1) * sizeof(char));

    if (!*input_file_name)
        return ERROR_IN_MALLOC;

    strcpy(*input_file_name, argv[1]);

    if (argc == 2)
        return OK;
    

    *substr = malloc((strlen(argv[2]) + 1) * sizeof(char));

    if (!*substr)
        return ERROR_IN_MALLOC;

    strcpy(*substr, argv[2]);   

    return OK;
}


void free_args(char **input_file_name, char **substr)
{
    if (*input_file_name)
        free(*input_file_name);

    if (*substr)
        free(*substr);
}