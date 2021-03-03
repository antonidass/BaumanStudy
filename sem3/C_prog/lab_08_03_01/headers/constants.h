#ifndef ERRORS
#define ERRORS

#define OK 0
#define ERROR_IN_INPUT_SIZE -1
#define ERROR_IN_MATRIX_ALLOC -2
#define ERROR_IN_INPUT_DATA -3
#define ERROR_IN_INPUT_POWER -4

#define ERROR_IN_INPUT_SIZE_MSG "Error in input size of matrix\n"
#define ERROR_IN_MATRIX_ALLOC_MSG "Error while allocation memory\n"
#define ERROR_IN_INPUT_DATA_MSG "Error in input data\n"
#define ERROR_IN_INPUT_POWER_MSG "Error in input power\n"

#endif


#ifndef TYPES
#define TYPES

typedef int **matrix_t;
typedef int *row_t;

#endif
