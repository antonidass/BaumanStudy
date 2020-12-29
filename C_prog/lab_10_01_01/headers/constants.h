#include <stdlib.h>
#include <stdio.h>
#include "macrologger.h"



#ifndef CONSTANTS
#define CONSTANTS 

#define OK 0
#define EMPTY 1
#define NOT_EMPTY 0
#define LIST_EMPTY -1
#define ERROR_ARGS -2
#define MAX_FILE_NAME 100
#define ERROR_IN_OPEN_FILE -3
#define MAX_ELEMS_IN_FILE 100

typedef int (comp_func_t)(const void *, const void *);

#endif



#ifndef NODE_T
#define NODE_T

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

#endif




