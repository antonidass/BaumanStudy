#include "functions.h"



FUNC_DLL int FUNC_DECL mem_alloc(int **pb, int size)
{
    *pb = malloc((size_t)size * sizeof(int));
    
    if (pb == NULL)
        return ERROR_IN_MALLOC;

    return OK;
}

FUNC_DLL void FUNC_DECL mem_dealloc(int **p)
{
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
}


int *find_index_max_elem(int *pb_src, int *pe_src)
{
    int *p_max_elem = pb_src;

    while (pb_src != pe_src)
    {
        LOG_DEBUG("cur -> %d max_elem -> %d", *pb_src, *p_max_elem);
        if (*pb_src > *p_max_elem)
            p_max_elem = pb_src;

        pb_src++;
    }

    return p_max_elem;
}

int *find_index_min_elem(int *pb_src, int *pe_src)
{
    int *p_min_elem = pb_src;

    while (pb_src != pe_src)
    {
        LOG_DEBUG("cur -> %d min_elem -> %d", *pb_src, *p_min_elem);

        if (*pb_src < *p_min_elem)
            p_min_elem = pb_src;

        pb_src++;
    }
    
    return p_min_elem;
}


FUNC_DLL void FUNC_DECL filter(const int *p_left, const int *p_right, int *pb_dst, int **pe_dst)
{
    while (++p_left != p_right)
    {   
        LOG_DEBUG("*p_left = %d", *p_left);
        *pb_dst = *p_left;
        pb_dst++;
        LOG_DEBUG("cur elem = %d ", *pb_dst);
    }

    *pe_dst = pb_dst;
}

FUNC_DLL int FUNC_DECL key(int *pb_src, int *pe_src, edges_t *edges)
{
    if (pe_src <= pb_src || pb_src == NULL || pe_src == NULL)
        return EMPTY_ARRAY_ERR;

    int *p_max_elem = find_index_max_elem(pb_src, pe_src);
    int *p_min_elem = find_index_min_elem(pb_src, pe_src);

    int count_elements = abs((int) (p_max_elem - p_min_elem));

    if (count_elements <= 1)
        return NO_ELEMENTS_BETWEEN_ERROR;

    if (p_max_elem > p_min_elem)
    {
        edges->left = p_min_elem;
        edges->right = p_max_elem;
    }
    else
    {
        edges->left = p_max_elem;
        edges->right = p_min_elem;
    }

    return OK;
}


FUNC_DLL int FUNC_DECL comp(const void *first, const void *second)
{
    return *((int *)first) - *((int *)second);        
}

void remember_elem(char *src_byte, char *dst_byte, int size)
{
    for (int i = 0; i < size; i++)
        *dst_byte++ = *src_byte++;
}


char *binary_search(char *copy_pb, char *item_p, char *l, char *r, int size, comp_function_t comp_function)
{
    if (r <= l)
    {
        if (comp_function(item_p, l) > 0)
            return l + size;
        return l;
    }

    char *mid = copy_pb + (((l - copy_pb) + (r - copy_pb)) / 8) * size;

    LOG_DEBUG("recreation =  %I64d ", ((l - copy_pb) + (r - copy_pb)) / 8);
    LOG_DEBUG("mid = %p    *mid = %d    l = %p  r = %p   *l = %d  *r = %d  copy_pb = %p ", mid, *mid, l, r, *l, *r, copy_pb);
    
    if (comp_function(item_p, mid) == 0)
        return mid + size;
 
    if (comp_function(item_p , mid) > 0)
        return binary_search(copy_pb, item_p, mid+size, r, size, comp_function);

    return binary_search(copy_pb, item_p, l, mid-size, size, comp_function);
}
 


FUNC_DLL void FUNC_DECL mysort(void *pb, int total_elems,  int size, comp_function_t *comp_function)
{
    if (total_elems == 0)
        return;

    char* copy_pb = (char *) pb;
    char *i, *loc, *j;
    char *head_byte_of_selected_elem = malloc(size);

    if (head_byte_of_selected_elem == NULL)
        return;

    for (i = copy_pb + size; i < copy_pb + total_elems * size; i += size)
    {
        j = i - size;
        remember_elem(i, head_byte_of_selected_elem, size);

        LOG_DEBUG("*i ================ %d        i =  %p   *j = %d     j = %p", *(int*)i, i, *(int *)j, j);
        loc = binary_search(copy_pb, head_byte_of_selected_elem, copy_pb, j, size, comp_function);

        LOG_DEBUG("loc = %p   *loc = %d    selected =  %d  i =  %p  *i = %d" , loc, *loc, *(int*)head_byte_of_selected_elem, i, *i);

        while (j >= loc)
        {
            remember_elem(j, j + size, size);
            j -= size;
        }
        remember_elem(head_byte_of_selected_elem, j + size, size);
    }

    if (head_byte_of_selected_elem != NULL)
    {
        free(head_byte_of_selected_elem);
        head_byte_of_selected_elem = NULL;
    }
}





FUNC_DLL int FUNC_DECL print_error(int error, FILE *stream)
{
    if (error == ERROR_IN_MALLOC)
    {
        fprintf(stream, ERROR_IN_MALLOC_MSG);
        return ERROR_IN_MALLOC;
    }

    if (error == EMPTY_DATA_ERROR)
    {
        fprintf(stream, EMPTY_DATA_ERROR_MSG);
        return EMPTY_DATA_ERROR;
    }

    if (error == NO_ELEMENTS_BETWEEN_ERROR)
    {
        fprintf(stream, NO_ELEMENTS_BETWEEN_ERROR_MSG);
        return NO_ELEMENTS_BETWEEN_ERROR;
    }

    return OK;
}


FUNC_DLL int FUNC_DECL parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, int *filter)
{
    if (argc > 4 || argc < 3)
    {
        fprintf(stderr, ERROR_ARGS_MSG);
        return ERROR_ARGS;
    }

    if (argc == 4 && strcmp(argv[3], "f") != 0)
    {
        fprintf(stderr, ERROR_ARG_FILTER_MSG);
        return ERROR_ARG_FILTER;
    }

    if (argc == 4)
        *filter = YES;

    strcpy(input_file_name, argv[1]);
    strcpy(output_file_name, argv[2]);
    
    return OK;
}