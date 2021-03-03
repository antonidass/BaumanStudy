#include "iostream.h"
#include "data_structures.h"



/*
table_info: Information about program
*/
void table_info()
{
       printf("%s",
              "Деление числа с плавающей точкой на целое число\n\n" 
              "Правила ввода:\n" 
              "* Знак '+' перед числом не обязателен.\n"
              "* При экспоненциальной записи обязательны буквы: латинская 'E' или 'e'.\n"
              "* Знак перед порядком не обязателен к вводу ('+' или '-').\n"
              "* Ведущие нули недопустимы.\n"
              "* Вещественная точка может записываться ТОЛЬКО в виде точки "
              "(запятая ',' недопустима).\n"
              "* Максимальная длина целого числа 30 символов, без учета знака.\n"
              "* Максимальная длина вещественного числа 39 символов "
              "(1 символ на знак числа, 1 символ на точку, "
              "30 символов на мантиссу, 1 символ на знак экспоненты, "
              "1 символ на знак порядка, 5 символов на порядок.\n\n"
              "* Запрещается вводить целое число в вещественном формате (3.0, 20000.000 и т.д)");
}

/*
float_input: Input of float number
*/
int float_input(char *float_number, FILE *stream)
{
    printf("%s",
            "                             |          мантисса          |\n"
            "                             |--------|---------|---------|\n"
            "                             1       10        20         30\n" 
            "Введите вещественное число:  ");
    if (fgets(float_number, MAX_FLOAT_SYMBOLS, stream) == NULL)
        return READ_ERROR;
    return OK;
}


/*
int input: Input of integer number
*/
int int_input(char *integer_number, FILE *stream)
{
    printf("%s",
            "                                     целая часть         |\n"
            "                            |--------|---------|---------|\n"
            "                            1       10        20        30\n"
            "Введите целое число:        ");
    if (fgets(integer_number, MAX_INT_SYMBOLS+3, stream) == NULL)
        return READ_ERROR;
    return OK;
}



/*
int parse_float: validate float number
*/
int parse_float(char *float_num, float_num_t *num_t)
{
    num_t->sign_of_mantissa = ' ';
    num_t->sign_of_order = ' ';
    char order[MAX_ORDER + 1];
    int  j = 0, i = 0, sign_check = 0, digit_before_point = 0;

    if (*float_num == '\n')
        return DATA_ERR;

    while (*float_num != '\0')
    {
        if (i > MAX_MANTISSA)
        {
            return MANTISSA_LEN_ERR;
        }
        else if (i > MAX_ORDER && sign_check == 2)
        {
            return ORDER_OVERFLOW_ERR;
        }
        else if ((*float_num == '+' || *float_num == '-') && num_t->sign_of_mantissa != ' ' && num_t->sign_of_order != ' ')
        {
            return INCORRECT_FLOAT;
        }
        else if ((*float_num == '+' || *float_num == '-') && num_t->sign_of_mantissa == ' ' && sign_check == 0)
        {
            num_t->sign_of_mantissa = *float_num;
        }
        else if ((*float_num == '+' || *float_num == '-') && num_t->sign_of_order == ' ' && (sign_check == 1 || sign_check == 2))
        {
            num_t->sign_of_order = *float_num;
        }
        else if (*float_num >= '0' && *float_num  <= '9' && sign_check == 0)
        {
            num_t->field_of_mantissa[i++] = *float_num - '0';
            digit_before_point++;
        }        
        else if (*float_num == '.' && sign_check == 1)
        {
            return INCORRECT_FLOAT;
        }
        else if (*float_num == '.' && sign_check == 0)
        {
            sign_check = 1;
        }
        else if (*float_num == 'E' || *float_num == 'e')
        {
            sign_check = 2;
        }
        else if (*float_num >= '0' && *float_num <= '9' && sign_check == 1)
        {
            num_t->field_of_mantissa[i++] = *float_num - '0';
        }
        else if (*float_num >= '0' && *float_num <= '9' && sign_check == 2)
        {
            order[j++] = *float_num;
        }
        else if (*float_num != ' ' && *float_num != '\n')
        {
        return INCORRECT_FLOAT;
        }

        float_num++;
    }
    
    num_t->mantissa_len = i;

    if (num_t->sign_of_order == '-')
        num_t->order = -atoi(order) + digit_before_point;

    else if (num_t->sign_of_order == '+' || num_t->sign_of_order == ' ')
        num_t->order = atoi(order) + digit_before_point;
    
    return OK;
}

/*
int parse_int: validate int number
*/
int parse_int(char *int_num, int num_array[], int *sign_int)
{
    int i = 0;

    while (*int_num != '\n')
    {
        if (*int_num == '.' || *int_num == 'E' || *int_num == 'e')
        {
            return INT_NO_FLOAT_ERR;
        }
        else if (*int_num == '-')
        {
            *sign_int = '-';
        }
        else if (*int_num >= '0' && *int_num <= '9')
        {
            num_array[i++] = *int_num - '0';
        }
        else if (*int_num != '+')
        {
            return INCORRECT_INT;
        }

        if (i > MAX_INT_SYMBOLS)
            return MAX_INT_SYMBOLS_ERR;
        
        int_num++;
    }

    if (i == 0)
        return NO_DATA;

    return i;
}





/*
print_answer: Print result of division
*/
int print_answer(float_num_t num)
{
    if (num.order <= -100000 || num.order >= 100000)
    {
        printf("Переполнение порядка!\n");
        return ORDER_OVERFLOW_ERR;
    }

    printf("Результат деления = ");
    if (num.mantissa_len == 0)
        printf("0\n");
    
    else
    {
        printf("%c0.", num.sign_of_mantissa);
        for (int i = 0; i < num.mantissa_len; i++)
            printf("%d", num.field_of_mantissa[i]);
        printf("E%d\n", num.order);
    }
    return OK;
}
