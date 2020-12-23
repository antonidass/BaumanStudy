#pragma once

#include "constants.h"

typedef union
{
    struct
    {
        int repair;
    } primary_t;
    
    struct 
    {
        int build_year;
        int owners_quantity;
        int tenat_quantity;
        int were_pet;
    } secondary_t;
} flat_type_info;


typedef struct
{
    char address[MAX_ADDRESS];
    int square;
    int room_amount;
    int price_per_meter;
    int flat_type;
    flat_type_info flat_info;

} flat_t;
