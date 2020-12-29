#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define OK 0
#define MAX_OBJECT_NAME 26
#define MAX_OBJECTS 15
#define EPS 1e-5
#define POSITIVE_NUMBER 1
#define NEGATIVE_NUMBER -1
#define ZERO 0

#define AMOUNT_PARAMS_ERR -1
#define FILE_NAME_ERR -2
#define DATA_ERR -3
#define LEN_WORD_ERR -4
#define MAX_OBJECTS_ERR -5
#define ZERO_SUBSTRING_OBJECTS_ERR -6
#define ERROR_IN_READ -7
#define FILE_CLOSE_ERR -8


typedef struct object
{
    char name[MAX_OBJECT_NAME];
    double mass;
    double volume;
    double density;
} object_t;

int read_objects(FILE *file, object_t objects[]);
void print_objects(object_t objects[], int n);
int compare(const void *x1, const void *x2);
int find_substring_words(object_t objects[], int n, char substring[], object_t substring_objects[]);
int check_data(const double *first, const double *second);