

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES 

typedef struct 
{
    int *matrix;
    int row;
    int column;
} matrix_t;

typedef struct
{
    int *values;
    int *columns;
    int *pointers;
    int elems_amount;
    int row;
} sparse_matrix_t;


typedef struct
{
    int *values;
    int *indexes;
    int not_null_elems_amount;
    int all_elems_amount;
} sparse_vector_t;

#endif

