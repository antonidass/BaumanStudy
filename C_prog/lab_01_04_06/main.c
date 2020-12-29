#include <stdio.h>
#include <math.h>

#define EPS 1e-5
#define YES 1 // Принадлежит отрезку
#define NO 0  // Не принадлежит
#define ERROR 2 // Неверные входные данные
#define OK 0


// Проверка принадлежности интервалу: x1 < x_a < x2
int belong_interval(double x_1, double x_2, double xa)
{
    if (((xa - x_1 >= 0) && (x_2 - xa >= 0)) || ((xa - x_2 >= 0) && (x_1 - xa >= 0)))
        return YES;

    return NO;
}

// Проверка принадлежности отрезку
int belong_segment(double x_1, double y_1, double x_2, double y_2, double xa, double ya)
{
    int interval_condition = 0, segment_condition = 0;
	
    if (belong_interval(x_1, x_2, xa))
        interval_condition = 1;

    if ((fabs((xa - x_1) * (y_2 - y_1) - (ya - y_1) * (x_2 - x_1)) <= EPS))
        segment_condition = 1;

    if (interval_condition * segment_condition == 1)
        return YES;

    return NO;
}


// Ввод и проверка входных данных
int input_and_check(double *x_1, double *y_1, double *x_2, double *y_2, double *xa, double *ya)
{
    int rc;

    printf("Input x1, y1, x2, y2, xA, yA ");
    rc = scanf("%lf%lf%lf%lf%lf%lf", x_1, y_1, x_2, y_2, xa, ya);

    if (rc != 6 || (fabs(*x_1 - *x_2) <= EPS && fabs(*y_1 - *y_2) <= EPS))
    {
        printf("Input wrong data");
        return ERROR;
    }

    return OK;
}

int main()
{	
    double x_1, y_1, x_2, y_2, xa, ya;
    int error_check;

    error_check = input_and_check(&x_1, &y_1, &x_2, &y_2, &xa, &ya);

    if (error_check == ERROR)
        return ERROR;

    int ans = belong_segment(x_1, y_1, x_2, y_2, xa, ya);

    printf("%d", ans);

    return OK;
}
