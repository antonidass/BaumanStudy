#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "../headers/work_with_list.h"
#include "../headers/mem_manager.h"
#include "../headers/functions.h"
#include "../headers/iostream.h"

#define ERROR_IN_LEN -1
#define ERROR_IN_CMP -2
#define OK 0

int lists_cmp(node_t *first, node_t *second);