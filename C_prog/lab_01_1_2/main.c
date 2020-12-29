#include <stdio.h>
#include <math.h>

#define OK 0
#define PI_DIVIDED_BY_180 (4*atan(1) / 180)
#define HALF 2

int main()
{
    float a, b, alpha, h, s;

    printf("Input a, b, alpha ");
    scanf("%f%f%f", &a, &b, &alpha);

    h = (fabs(a - b) / HALF) * tan(PI_DIVIDED_BY_180 * alpha);
    s = h * ((a + b) / HALF);

    printf("%.5f", s);

    return OK;
}
