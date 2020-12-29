#include <stdio.h>
#include "my_strpbrk.h"

#define ASCII_SIZE 128

char *my_strpbrk(const char *str_first, const char *str_second)
{
    const char *str_second_iterative = str_second;
    
    while (*str_first != *str_second_iterative++ && *str_first != '\0')
    {
        if (*str_second_iterative == '\0')
        {
            str_second_iterative = str_second;
            str_first++;
        }
    }

    if (*str_first == '\0')
        return NULL;

    return (char*) str_first;
}

char *my_strpbrk2(const char *str_first, const char *str_second)
{
    char flags[ASCII_SIZE] = { 0 };

    for (const char *i = str_second; *i != '\0'; i++)
        flags[(int) *i] = 1;

    while (*str_first++ != '\0')
    {
        if (flags[(int) *str_first])
            return (char*) str_first;
    }
    
    return NULL;
}

