#include <stdio.h>

#define OK 0
#define FLATS_IN_ENTRANCE 36
#define FLATS_ON_FLOOR 4

int main()
{
    int n, entrance_number, floor_number;

    printf("Input flat number ");
    scanf("%d", &n);

    entrance_number = (n + FLATS_IN_ENTRANCE - 1) / FLATS_IN_ENTRANCE;
    n = n - (entrance_number - 1) * FLATS_IN_ENTRANCE;
    floor_number = (n + FLATS_ON_FLOOR - 1) / FLATS_ON_FLOOR;

    printf("Entrance = %d Floor = %d", entrance_number, floor_number);

    return OK;
}
