#include "functions.h"


int check_data(const double *first, const double *second)
{
    if (*first < EPS || *second < EPS)
        return DATA_ERR;

    return OK;
}

int read_objects(FILE *file, object_t objects[])
{    
    int i = 0;

    while (!feof(file))
    {
        if (i >= MAX_OBJECTS)
            return MAX_OBJECTS_ERR;
        
        if (fgets(objects[i].name, MAX_OBJECT_NAME + 2, file) == NULL)
            return ERROR_IN_READ;
        
        if (strlen(objects[i].name) > MAX_OBJECT_NAME)
            return LEN_WORD_ERR;
        
        int rc = 0;

        rc = fscanf(file, "%lf\n", &objects[i].mass);
        if (rc != 1)
            return ERROR_IN_READ;

        rc = fscanf(file, "%lf\n", &objects[i].volume);
        if (rc != 1)
            return ERROR_IN_READ;

        if (check_data(&objects[i].mass, &objects[i].volume))
            return DATA_ERR;
        
        objects[i].density = objects[i].mass / objects[i].volume;

        i++;
    }
    return i;
}

void print_objects(object_t objects[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s%lf\n%lf\n", objects[i].name, objects[i].mass, objects[i].volume);
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
        while (substring[j] == objects[i].name[j])
            j++;
        
        if (substring[j] == '\0')
            substring_objects[count_substring_words++] = objects[i];
    }
    return count_substring_words;
}