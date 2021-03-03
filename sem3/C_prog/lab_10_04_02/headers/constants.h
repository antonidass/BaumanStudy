#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "macrologger.h"


#ifndef CONSTANTS
#define CONSTANTS

#define OK 0
#define MAX_STRING_LEN 100
#define ERROR_IN_INPUT_COMMAND -1
#define ERROR_IN_INPUT_NUM -2
#define ERROR_IN_DIV -3
#define ERROR_IN_MUL -4

#endif


#ifndef DATA_S
#define DATA_S

typedef enum commands
{
    out,
    mul,
    sqr,
    div_
} commands_t;


typedef struct list_num_node list_num_node_t;

struct list_num_node
{
    int num;
    int pow;
    list_num_node_t *next;
    list_num_node_t *prev;
};

#endif