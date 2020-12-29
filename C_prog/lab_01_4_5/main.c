#include <stdio.h>

#define ERROR -1 // Неверные входные данные
#define OK 0    // Программа завршилась без ошибок

// Поиск делителей
void find_dividers(int n)
{
    int k = 2;

    if (n == 1)
        return;
    
    printf("Dividers: ");

    while (k * k <= n)
    {
        while (n % k == 0)
        {
            printf("%d ", k);
            n = n / k;
        }
        k++;
    }

    if (n > 1)
        printf("%d", n);
}

// Проверка входных данных
int check_input()
{
    int n, rc;

    printf("Input n ");
    rc = scanf("%d", &n);

    if (rc != 1 || n <= 0)
    {
        printf("Wrong input data");
        return ERROR;
    }

    return n;
}

int main()
{
    int n;

    n = check_input();

    if (n == ERROR)
        return ERROR;

    find_dividers(n);

    return OK;
}
