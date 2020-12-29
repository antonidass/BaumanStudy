#include <stdio.h>
#include <math.h>

#define ERROR -1 // Неверные входные данные
#define OK 0    // Программа завершилась без ошибок
#define EPS 1e-6

// Значение функции
float f(float x)
{
    return 1 / ((1 + x) * (1 + x) * (1 + x));
}

// Абсолютная ошибка
float absolute_error(float function, float s)
{
    return fabsf(function - s);
}

// Относительная ошибка
float relative_error(float absolute, float function)
{
    return fabsf(absolute / function);
}

// Вычисление суммы ряда
float row_sum(float x, float eps)
{
    float s = 1.0, t = 1.0;
    int sign = 1, n = 1;

    while (fabsf(t * n * (n + 1) / 2) >= eps)
    {
        n += 1;
        sign *= -1;
        t *= x;
        s += sign * t * n * (n + 1) / 2;
    }

    return s;
}

// Ввод данных
float input_float()
{
    int rc;
    float value;

    rc = scanf("%f", &value);

    if (rc != 1)
        return ERROR;

    return value;
}

// Проверка входных данных
int check_input(float x, float eps)
{
    if (x - ERROR <= EPS || eps - ERROR <= EPS  || fabs(x) >= 1 || eps > 1 || eps < 0)
    {
        printf("Input wrong data");
        return ERROR;
    }

    return OK;
}

// Вывод на экран
void output(float s, float f, float abs, float rel)
{
    printf("s = %.5f f = %.5f absolute = %.5f relative = %.5f", s, f, abs, rel);
}

int main()
{   
    float x = input_float(), eps = input_float();

    printf("Input x, eps ");

    int error_check = check_input(x, eps);

    if (error_check == ERROR)
        return ERROR;

    float s, relative, absolute, function;

    s = row_sum(x, eps);
    function = f(x);
    absolute = absolute_error(function, s);
    relative = relative_error(absolute, function);

    output(s, function, absolute, relative);

    return OK;
}
