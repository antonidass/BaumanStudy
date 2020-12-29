#include <stdio.h>
#include "my_iostream.h"
#include "my_functions.h"


int my_getline(char *str)
{
    int c, count = 0, i = 0;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i > MAX_LINE_LEN)
            return LEN_LINE_ERR;

        count += is_separator(c);
        str[i++] = c;
    }

    if (c == EOF)
        return CANNOT_READ_ERR;
    
    if (count == i)
        return NO_WORDS_ERR;

    if (i == 0)
        return EMPTY_ERR;
    
    str[i] = '\0';

    return count;
}

void my_out(char words[][MAX_LETTERS], int answers[], int n)
{
    printf("Result:\n");

    for (int i = 0; i < n; i++)
        printf("%s %s \n", words[i], answers[i] == 1 ? "yes" : "no");
}