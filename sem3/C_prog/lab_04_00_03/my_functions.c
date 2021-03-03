#include <stdio.h>
#include "my_functions.h"
#include <string.h>


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

int str_equality(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *str1 == *str2;
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
            strcpy(words[j++], word);
        }
    }

    if (letter_counter != 0)
    {
        word[letter_counter] = '\0';
        strcpy(words[j++], word);
    }

    return j;
}

void shift(char *str, int pos)
{
    int i = pos;

    while ((str[i] = str[i + 1]) != '\0')
        i++;

    str[i + 1] = '\0';
}

void delete_symbols(char *str, char symbol)
{
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == symbol)
        {
            shift(str, i);
            i--;
        }
    }
}

void form_string(char *result_str, char words[][MAX_LETTERS], int words_count)
{
    for (int i = words_count - 1; i >= 0; i--)
    {
        if (strcmp(words[words_count - 1], words[i]))
        {
            delete_symbols(words[i], words[i][0]);

            strcat(result_str, words[i]);
            i != 0 ? strcat(result_str, " ") : 0;
        }
    }
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