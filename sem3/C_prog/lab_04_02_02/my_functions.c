#include <stdio.h>
#include "my_functions.h"


int is_separator(int c)
{
    char separator[] = " ,;:-.!?";

    for (int i = 0; separator[i] != '\0'; i++)
    {
        if (c == separator[i])
            return YES;
    }

    return NO;
}

void my_strcpy(const char *s1, char *s2)
{
    while ((*s2++ = *s1++) != '\0') ;

    *s2 = '\0';
}

int str_equality(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *str1 == *str2;
}

int repeat_check(const char *str, char words[][MAX_LETTERS], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (str_equality(str, words[i]))
            return YES;
    }
    
    return NO;
}

int my_split(const char *str, char words[][MAX_LETTERS])
{
    char word[MAX_LETTERS];
    int i = 0, j = 0, letter_counter = 0;

    while (str[i] != '\0')
    {
        if (letter_counter > MAX_LETTERS)
            return WORD_LEN_ERR;

        if (!is_separator(str[i]))
        {
            word[letter_counter] = str[i];
            letter_counter++;
        }
        
        if (is_separator(str[i++]) && letter_counter != 0)
        {   
            word[letter_counter] = '\0';
            letter_counter = 0;

            if (!repeat_check(word, words, j))
                my_strcpy(word, words[j++]);
        }
    }

    if (letter_counter != 0)
    {
        word[letter_counter] = '\0';
        if (!repeat_check(word, words, j))
            my_strcpy(word, words[j++]);
    }

    return j;
}


int my_strstr(const char *first, char words_second[][MAX_LETTERS], int words_second_count)
{
    for (int i = 0; i < words_second_count; i++)
    {
        if (str_equality(first, words_second[i]))
            return YES;
    }

    return NO;
}


int errors_check(const int rc)
{
    if (rc == LEN_LINE_ERR)
    { 
        fprintf(stderr, LEN_LINE_MSG);
        return LEN_LINE_ERR;
    }

    if (rc == NO_WORDS_ERR)
    {
        fprintf(stderr, NO_WORDS_MSG);
        return NO_WORDS_ERR;
    }
    
    if (rc == CANNOT_READ_ERR)
    {
        fprintf(stderr, FIND_EOF_MSG);
        return CANNOT_READ_ERR;
    }
    
    if (rc == EMPTY_ERR)
    {
        fprintf(stderr, EMPTY_LINE_MSG);
        return EMPTY_ERR;
    }
    
    if (rc == WORD_LEN_ERR)
    {
        fprintf(stderr, LEN_WORD_MSG);
        return WORD_LEN_ERR;
    }

    return rc;
}


void form_answers(int *answers, int word_count_first, char words_second[][MAX_LETTERS], int word_count_second, char words_first[][MAX_LETTERS])
{
    for (int i = 0; i < word_count_first; i++)
        answers[i] = my_strstr(words_first[i], words_second, word_count_second);
}