#ifndef __LIST_UTILS_H__
#define __LIST_UTILS_H__

#include "constants.h"


typedef struct list
{
    char *value;
    struct list *next;
} list_t;


int linsert(list_t **arr, char *buffer);



#endif