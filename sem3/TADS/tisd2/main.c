#include "constants.h"
#include "iostream.h"
#include "data_structures.h"
#include "sorts.h"


int main()
{
    flat_t flats[MAX_FLATS];
    

    FILE *file = fopen("data.txt", "r");


    int ans = input_data(file, flats);

    int keys[MAX_FLATS];

    for (int i = 0; i < ans; i++)
    {
        keys[i] = i;
    }

    int rc = main_menu(flats, &ans, keys);

    if (rc < 0)
        return rc;


    return OK;
}