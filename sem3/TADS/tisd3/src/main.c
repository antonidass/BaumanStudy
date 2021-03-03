#include "../headers/iostream.h"
#include "../headers/functions.h"

int main()
{
    matrix_t matrix, res_matrix, vector;
    sparse_matrix_t sparse_matrix;
    sparse_vector_t svector, sres;

    sparse_matrix.columns = NULL;
    sparse_matrix.pointers = NULL;
    sparse_matrix.values = NULL;
    svector.indexes = NULL;
    svector.values = NULL;
    sres.values = NULL;
    sres.indexes = NULL;
    res_matrix.matrix = NULL;

    res_matrix.row = -1;
    res_matrix.column = -1;
    
    int rc = main_menu(&matrix, &vector, &res_matrix, &sparse_matrix, &svector, &sres);

    free_all(&matrix, &vector, &res_matrix, &sparse_matrix, &svector, &sres);
   

    if (rc != OK)
        return rc;

    return OK;
}