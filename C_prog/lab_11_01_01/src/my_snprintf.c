#include "../headers/my_snprintf.h"



void my_strncpy(char *dst, char *src, size_t max_size, size_t *cur_size)
{
    while (*src)
    {
        if (dst && max_size && *cur_size < max_size)
            *(dst + *cur_size) = *src;

        (*cur_size)++;
        src++;
    }
}



int get_len_num(int num)
{
    int len = 0;

    while (num)
    {
        len++;
        num /= 10;
    }
    
    return len;
}


char *hd_to_str(int num)
{
    char *str = NULL;

    if (num == 0)
    {
        str = malloc(sizeof(char) * 2);
        str[0] = 0;
        str[1] = '\0';

        return str;
    }


    int len = get_len_num(abs(num));

    if (num < 0)
        len++;
        
    str = malloc(sizeof(char) * (len + 1));

    LOG_DEBUG("len = %d", len);

    int temp_num = abs(num);

    for (int i = 0; i < len; i++, temp_num /= 10)
        str[len - i - 1] = temp_num % 10 + '0';  
    
    if (num < 0)
        str[0] = '-';
    
    str[len] = '\0';

    LOG_DEBUG("hd to str = %s ", str);

    return str;
}



int my_snprintf(char *string, size_t size, const char *format, ...)
{
    va_list vl;
    va_start(vl, format);

    size_t cur_size = 0;
    
    while (*format)
    {
        if (*format == '%')
        {
            format++;

            if (*format == 's')
            {
                char *arg_str = va_arg(vl, char *);

                my_strncpy(string, arg_str, size, &cur_size);

                LOG_DEBUG("size = %ld   cur_size = %ld   ", size, cur_size);
            }
            else if (*format == 'c')
            {
                int symbol = va_arg(vl, int);

                *(string + cur_size) = (char) symbol;

                cur_size++;
            }
            else if (*format++ == 'h' && *format == 'd')
            {
                int num = va_arg(vl, int);

                char *str_num = hd_to_str(num);

                my_strncpy(string, str_num, size, &cur_size);

                free(str_num);
            }

            format++;
        }
        else
        {
            LOG_DEBUG("cur_size = %ld size = %ld", cur_size, size);

            if (string && size && cur_size < size)
                *(string + cur_size) = *format;
            
            format++;

            cur_size++;
        }

    } 

    va_end(vl);

    if (string && size)
    {
        if (cur_size < size)
            *(string + cur_size) = '\0';
        else
            *(string + size - 1) = '\0';
    }
    
    return cur_size;
}