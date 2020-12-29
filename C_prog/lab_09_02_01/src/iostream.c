#include "../headers/iostream.h"


char *buf = NULL;
int buf_size = 100;


int count_elems(FILE *file)
{
    int k = 0;

    if (!buf)
    {
        buf = malloc(sizeof(char) * buf_size);

        if (!buf)
            return ERROR_IN_MALLOC;
    }

    while (fscanf(file, "%s", buf) != EOF && ++k) ;

    LOG_DEBUG("k = %d", k);

    free(buf);
    buf = NULL;

    if (k % OBJECT_FIELD_AMOUNT != 0)
        return ERROR_IN_FIELD;

    if (!k)
        return EMPTY_FILE_ERROR;
        
    return k;
}


int get_line_len(FILE *file)
{
    int i = 0;
    char c;

    if (!buf)
    {
        buf = malloc(sizeof(char) * buf_size);

        if (!buf)
            return ERROR_IN_MALLOC;
    }

    while ((c = getc(file)) != '\n')
    {
        *(buf + i) = c;
        i++;

        if (i == buf_size)
        {
            buf_size *= 2;
            buf = realloc(buf, buf_size * sizeof(char));

            if (!buf)
                return ERROR_IN_MALLOC;
        }
    }
    
    *(buf + i) = '\0';

    return i;
}


int read_objects(FILE *file, object_t objects[])
{    
    int i = 0;
    int line_len;

    while (!feof(file))
    {
        line_len = get_line_len(file);

        if (line_len <= 0)
        {
            free(buf);
            return ERROR_IN_MALLOC;
        }

        objects[i].name = malloc(sizeof(char) * (line_len + 1));

         if (!objects[i].name)
         {
            free(buf);
            return ERROR_IN_MALLOC;
         }

        strcpy(objects[i].name, buf);
        
        int rc = 0;

        rc = fscanf(file, "%lf\n", &objects[i].mass);
        if (rc != 1)
        {
            free(buf);
            return ERROR_IN_READ;
        }

        rc = fscanf(file, "%lf\n", &objects[i].volume);
        if (rc != 1)
        {
            free(buf);
            return ERROR_IN_READ;
        }

        if (check_data(&objects[i].mass, &objects[i].volume))
        {
            free(buf);
            return DATA_ERR;
        }

        objects[i].density = objects[i].mass / objects[i].volume;

        i++;
    }


    free(buf);
    return OK;
}


void print_objects(object_t objects[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n%lf\n%lf\n", objects[i].name, objects[i].mass, objects[i].volume);
    }  
}

