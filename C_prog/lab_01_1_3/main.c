#include <stdio.h>

#define OK 0

int main()
{
    float v1, v2, t1, t2, v, t;

    printf("Input v1, t1, v2, t2 ");
    scanf("%f%f%f%f", &v1, &t1, &v2, &t2);

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("v = %.5f t = %.5f", v, t);

    return OK;
}
