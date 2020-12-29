#include <stdio.h>
#include <string.h>
#include "my_functions.h"
#include "my_iostream.h"

int main()
{
    char first_str[MAX_LINE_LEN], second_str[MAX_LINE_LEN];

    int rv1 = my_getline(first_str);

    if (errors_check(rv1) < 0)
        return rv1;

    int rv2 = my_getline(second_str);

    if (errors_check(rv2) < 0)
        return rv2;

    char words_first[MAX_WORDS][MAX_LETTERS], words_second[MAX_WORDS][MAX_LETTERS];

    int word_count_first = my_split(first_str, words_first), answers[MAX_WORDS];

    if (errors_check(word_count_first) < 0)
        return word_count_first;
    
    int word_count_second = my_split(second_str, words_second);

    if (errors_check(word_count_second) < 0)
        return word_count_second;

    form_answers(answers, word_count_first, words_second, word_count_second, words_first);

    my_out(words_first, answers, word_count_first);

    return OK;
}