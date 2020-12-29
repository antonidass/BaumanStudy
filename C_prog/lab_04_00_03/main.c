#include <stdio.h>
#include <string.h>
#include "my_functions.h"
#include "my_iostream.h"

int main()
{
    char str[MAX_LINE_LEN];
    int rv = my_getline(str);

    if (errors_check(rv) < 0)
        return rv;

    char words[MAX_WORDS][MAX_LETTERS];

    int word_count = my_split(str, words);

    if (errors_check(word_count) < 0)
        return word_count;

    char result_str[MAX_RESULT_LEN] = "";

    
    form_string(result_str, words, word_count);

    if (!str_equality(result_str, ""))
    {
        printf("Result: %s\n", result_str);
        return OK;
    }

    return EMPTY_ERR;
}