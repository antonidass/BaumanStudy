#include "iostream.h"
#include "constants.h"
#include "functions.h"
#include "data_structures.h"


int main()
{
    table_info();

    char float_number[MAX_FLOAT_SYMBOLS + 1];
    char integer_number[MAX_INT_SYMBOLS + 3];
    float_num_t float_num;
    int_num_t int_num;
    
    int ans = float_input(float_number, stdin);
    ans += int_input(integer_number, stdin);

    if (ans != OK)
    {
        printf("Ошибка в чтении данных");
        return DATA_ERR;
    }

    ans = parse_float(float_number, &float_num);

    if (ans ==  INCORRECT_FLOAT)
    {
        printf("Ошибка в вводе вещественного числа");
        return ans;
    }

    if (ans == ORDER_OVERFLOW_ERR)
    {
        printf("Переполнение порядка");
        return ans;
    }

    if (ans == MANTISSA_LEN_ERR)
    {
        printf("Превышена длина мантиссы");
        return ans;
    }


    int_num.sign_of_num = (int) ' ';
    ans = parse_int(integer_number, int_num.number, &int_num.sign_of_num);

    if (ans == INCORRECT_INT)
    {
        printf("Целое число содержит недопустимые символы");
        return ans;
    }

    if (ans == MAX_INT_SYMBOLS_ERR)
    {
        printf("Превышено количество разрядов числа");
        return ans;
    }


    if (ans == NO_DATA)
    {
        printf("Пустой ввод целого числа");
        return ans;
    }

    if (ans == INT_NO_FLOAT_ERR)
    {
        printf("Целое число не может быть записано как вещественное");
        return ans;
    }


    int_num.number_len = ans;

    if (zero_check(int_num.number, int_num.number_len))
    {
        printf("Деление на ноль!\n");
        return DIV_BY_ZERO_ERR;
    }

    if (zero_check(float_num.field_of_mantissa, float_num.mantissa_len))
    {
        printf("Результат деления = +0.0E+0");
        return OK;
    }

    main_division(&float_num, &int_num);

    print_answer(float_num);
    
    return OK;
}