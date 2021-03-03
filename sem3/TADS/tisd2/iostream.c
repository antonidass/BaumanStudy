#include "constants.h"
#include "data_structures.h"
#include "sorts.h"




void read_line(char temp_line[], int *i, char data_in_line[])
{
    int j = 0;
    while (temp_line[*i] != ';' && temp_line[*i] != '\n' && temp_line[*i] != '\0')
    {
        data_in_line[j++] =  temp_line[*i];
        (*i)++;
    }
    (*i)++;
}

int input_data(FILE *data_file, flat_t flats[])
{
    int i = 0;
    while (!feof(data_file))
    {
        char temp_line[MAX_LINE] = {'\0'};

        int data_pointer = 0;
        fgets(temp_line, MAX_LINE, data_file);
        read_line(temp_line, &data_pointer, flats[i].address);

        char temp_square[MAX_LINE] = {'\0'};
        read_line(temp_line, &data_pointer, temp_square);
        flats[i].square = atoi(temp_square);

        char temp_rooms_amount[MAX_LINE] = {'\0'};
        read_line(temp_line, &data_pointer, temp_rooms_amount);
        flats[i].room_amount = atoi(temp_rooms_amount);

        char temp_price_per_meter[MAX_LINE] = {'\0'};
        read_line(temp_line, &data_pointer, temp_price_per_meter);
        flats[i].price_per_meter = atoi(temp_price_per_meter);

        char temp_flat_type[MAX_LINE] = {'\0'};
        read_line(temp_line, &data_pointer, temp_flat_type);

        if (strcmp(temp_flat_type, " primary") == 0)
        {
            flats[i].flat_type = PRIMARY;
        }
        else if (strcmp(temp_flat_type, " secondary") == 0)
        {
            flats[i].flat_type = SECONDARY;
        }
        else
        {
            return ERROR_IN_FLAT_TYPE;
        }
        
        if (flats[i].flat_type == PRIMARY)
        {
            char temp_repair[MAX_LINE] = {'\0'};
            read_line(temp_line, &data_pointer, temp_repair);

            if (strcmp(temp_repair, " yes") == 0)
            {
                flats[i].flat_info.primary_t.repair = WITH_REPAIR;
            }
            else if (strcmp(temp_repair, " no") == 0)
            {
                flats[i].flat_info.primary_t.repair = WITHOUT_REPAIR;
            }
            else
            {
                return ERROR_IN_REPAIR_DATA;
            }
        }
        else if (flats[i].flat_type == SECONDARY)
        {
            char temp_year[MAX_LINE] = {'\0'};
            read_line(temp_line, &data_pointer, temp_year);
            flats[i].flat_info.secondary_t.build_year = atoi(temp_year);

            char temp_owners[MAX_LINE] = {'\0'};
            read_line(temp_line, &data_pointer, temp_owners);
            flats[i].flat_info.secondary_t.owners_quantity = atoi(temp_owners);

            char temp_tenats[MAX_LINE] = {'\0'};
            read_line(temp_line, &data_pointer, temp_tenats);
            flats[i].flat_info.secondary_t.tenat_quantity = atoi(temp_tenats);

            char temp_pets_were[MAX_LINE] = {'\0'};
            read_line(temp_line, &data_pointer, temp_pets_were);

            if (strcmp(temp_pets_were, " yes") == 0)
            {
                flats[i].flat_info.secondary_t.were_pet = YES_PET;
            }
            else if (strcmp(temp_pets_were, " no") == 0)
            {
                flats[i].flat_info.secondary_t.were_pet = NO_PET;
            }
            else
            {
                return ERROR_IN_PETS_DATA;
            }
        }
        i++;
    }

    return i;
}

int find_special_data(flat_t flats[], int n_flats, flat_t special_flats[], int low_price_border, int high_price_border)
{
    int j = 0;
    for (int i = 0; i < n_flats; i++)
    {
        if (flats[i].flat_type == SECONDARY && flats[i].flat_info.secondary_t.were_pet == NO_PET && flats[i].room_amount == 2 &&
            flats[i].price_per_meter >= low_price_border && flats[i].price_per_meter <= high_price_border)
        {
            special_flats[j++] = flats[i];
        }
    }

    return j;
}

void print_flats(const flat_t flats[], int n_flats)
{
    printf("\n №          Адрес квартиры                        Площадь   Комнат  Цена за кв.м  Тип жилья   Отделка   Год постройки  Собственники  Жильцы  Животные\n\n");
    for (int i = 0; i < n_flats; i++)
    {


        printf("%2d    ", i + 1);
        if (flats[i].flat_type == SECONDARY)
        {
            printf("%40s     %3d        %d       %d         В          ---          %d         %d            %d       ",
            flats[i].address, flats[i].square, flats[i].room_amount, flats[i].price_per_meter, 
            flats[i].flat_info.secondary_t.build_year, flats[i].flat_info.secondary_t.owners_quantity, flats[i].flat_info.secondary_t.tenat_quantity);

            if (flats[i].flat_info.secondary_t.were_pet == YES_PET)
            {
                printf("да \n");
            }
            else
            {
                printf("нет \n");
            }   
        }


        if (flats[i].flat_type == PRIMARY)
        {
            printf("%40s     %3d        %d       %d         П          ", 
            flats[i].address, flats[i].square, flats[i].room_amount,  flats[i].price_per_meter);

            if (flats[i].flat_info.primary_t.repair == WITH_REPAIR)
            {
                printf("да           ---         ---          ---     ---\n");
            }
            else
            {
                printf("нет          ---         ---          ---     ---\n");
            }
        }
            

    }
}


int add_flat(flat_t flats[], int *n_flats)
{
    printf("Введите адрес квартиры БЕЗ пробелов через запятую ");
    int rc = scanf("%s", flats[*n_flats].address);

    if (rc != 1)
    {
        printf("Ошибка в записи адреса");
        return DATA_ERR;
    }

    printf("Введите количество квадратных метров ");
    rc = scanf("%d", &flats[*n_flats].square);
    if (rc != 1)
    {
        printf("Ошибка в записи кв.м");
        return DATA_ERR;
    }

    printf("Введите количество комнат ");
    rc = scanf("%d", &flats[*n_flats].room_amount);
    if (rc != 1)
    {
        printf("Ошибка в записи количества комнат");
        return DATA_ERR;
    }

    printf("Введите цену за квадратный метр ");
    rc = scanf("%d", &flats[*n_flats].price_per_meter);
    if (rc != 1)
    {
        printf("Ошибка в записи цены за кв.м");
        return DATA_ERR;
    }

    printf("Введите тип жилья (1 - первичка, 2 - вторичка) ");
    rc = scanf("%d", &flats[*n_flats].flat_type);
    if (rc != 1 || flats[*n_flats].flat_type < 1 || flats[*n_flats].flat_type > 2)
    {
        printf("Ошибка в выборе типа жилья");
        return DATA_ERR;
    }

    
    if (flats[*n_flats].flat_type == PRIMARY)
    {
        printf("\nС отделкой или без ?\n"
        "1 - с отделкой\n"
        "2 - без отделки\n");
        rc = scanf("%d", &flats[*n_flats].flat_info.primary_t.repair);
        if (rc != 1 || flats[*n_flats].flat_info.primary_t.repair > 2 || flats[*n_flats].flat_info.primary_t.repair < 1)
        {
            printf("Ошибка в выборе отделки");
            return DATA_ERR;
        }

    }

    else if (flats[*n_flats].flat_type == SECONDARY)
    {
        printf("\nВведите год постройки ");
        rc = scanf("%d", &flats[*n_flats].flat_info.secondary_t.build_year); 
        if (rc != 1 || flats[*n_flats].flat_info.secondary_t.build_year <= 0)
        {
            printf("Ошибка в записи года постройки\n");
            return DATA_ERR;
        }      

        printf("Введите количество собственников ");
        rc = scanf("%d", &flats[*n_flats].flat_info.secondary_t.owners_quantity);
        if (rc != 1)
        {
            printf("Ошибка в записи количества собственников\n");
            return DATA_ERR;
        }    

        printf("Введите количество жильцов ");
        rc = scanf("%d", &flats[*n_flats].flat_info.secondary_t.tenat_quantity);
        if (rc != 1)
        {
            printf("Ошибка в записи количества жильцов\n");
            return DATA_ERR;
        }    
        printf("Были ли питомцы (да - 1 / нет - 0) ");
        rc = scanf("%d", &flats[*n_flats].flat_info.secondary_t.were_pet);
        if (rc != 1 || flats[*n_flats].flat_info.secondary_t.were_pet > 1 || flats[*n_flats].flat_info.secondary_t.were_pet < 0)
        {
            printf("Ошибка в существовании питомцев"); 
            return DATA_ERR;
        }    
    }
    else
    {
        return DATA_ERR;
    }

    (*n_flats)++;
    return OK;
}

void delete_flat(flat_t flats[], int *n_flats, int num)
{
    for (int i = num - 1; i < *n_flats - 1; i++)
    {
        flats[i] = flats[i+1];
    }
    (*n_flats)--;
}

int delete_flat_info(flat_t flats[], int *n_flats, flat_t orig_flats[], int *orig_n)
{
    print_flats(orig_flats, *orig_n);
    printf("Выберите номер квартиры которую хотите удалить из списка ");
    int num;
    int rc = scanf("%d", &num);

    if (rc != 1 || num > *n_flats || num <= 0)
    {
        printf("Указанный номер не существует");
        return NO_NUMBER;
    }


    delete_flat(flats, n_flats, num);
    delete_flat(orig_flats, orig_n, num);

    return OK;
}


int add_flat_info()
{
    printf("Введите количество квартир, которых хотите добавить ");

    int n;
    int rc = scanf("%d", &n);

    if (rc != 1)
        return ERROR_IN_ADD_FLAT;
    
    return n;
}

void copy_flats(flat_t flats_origin[], int n, flat_t flats_destination[])
{
    for (int i = 0; i < n; i++)
    {
        flats_destination[i] = flats_origin[i];
    }
}

// Вывод исходной таблицы с отсортированными ключами
void print_sorted_table_keys(flat_t flats[], int n, int keys[])
{
    
    printf("\nКлючи    №          Адрес квартиры                        Площадь   Комнат  Цена за кв.м  Тип жилья   Отделка   Год постройки  Собственники  Жильцы  Животные\n\n");
    for (int i = 0; i < n; i++)
    {

        printf("  %2d    %2d    ", keys[i]+1, i+1);
        if (flats[i].flat_type == SECONDARY)
        {
            printf("%40s     %3d        %d       %d         В          ---          %d         %d            %d       ",
            flats[i].address, flats[i].square, flats[i].room_amount, flats[i].price_per_meter, 
            flats[i].flat_info.secondary_t.build_year, flats[i].flat_info.secondary_t.owners_quantity, flats[i].flat_info.secondary_t.tenat_quantity);

            if (flats[i].flat_info.secondary_t.were_pet == YES_PET)
            {
                printf("да \n");
            }
            else
            {
                printf("нет \n");
            }   
        }


        if (flats[i].flat_type == PRIMARY)
        {
            printf("%40s     %3d        %d       %d         П          ", 
            flats[i].address, flats[i].square, flats[i].room_amount,  flats[i].price_per_meter);

            if (flats[i].flat_info.primary_t.repair == WITH_REPAIR)
            {
                printf("да           ---         ---          ---     ---\n");
            }
            else
            {
                printf("нет          ---         ---          ---     ---\n");
            }
        }
    }
}

// Подсчет времени сортировок
void counting_time(flat_t flats[], int n, double elapsed_times[])
{
    flat_t copy_flats[MAX_FLATS];


    int copy_n = n;

    struct tms tmsBegin, tmsEnd;
    double elapsed_time;

    long double max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {
        for (int i = 0; i < n; i++)
        {
            copy_flats[i] = flats[i];
        }

        times(&tmsBegin);
        bubble_sort_for_value(copy_flats, copy_n);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }
    int j = 0;

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);



    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {
        for (int i = 0; i < n; i++)
        {
            copy_flats[i] = flats[i];
        }

        times(&tmsBegin);
        quick_sort_for_value(copy_flats, 0, n-1);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    int keys[MAX_FLATS];

    for (int i = 0; i < n; i++)
    {
        keys[i] = i;
    }

    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {
        for (int i = 0; i < n; i++)
        {
            copy_flats[i] = flats[i];
        }

        times(&tmsBegin);
        bubble_sort_for_key(copy_flats, n, keys);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    for (int i = 0; i < n; i++)
    {
        keys[i] = i;
    }

    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {
        for (int i = 0; i < n; i++)
        {
            copy_flats[i] = flats[i];
        }

        times(&tmsBegin);
        quick_sort_for_keys(copy_flats, 0, n-1, keys);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);
















    flat_t copy_flats2[MAX_FLATS];

    FILE *data2_1 = fopen("data_2.txt", "r");
    int n_2 = input_data(data2_1, copy_flats2);
    fclose(data2_1);



    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_value(copy_flats2, n_2);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    FILE *data2_2 = fopen("data_2.txt", "r");
    n_2 = input_data(data2_2, copy_flats2);
    fclose(data2_2);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_value(copy_flats2, 0, n_2-1);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    int keys2[MAX_FLATS];

    for (int i = 0; i < n; i++)
    {
        keys2[i] = i;
    }


    FILE *data2_3 = fopen("data_2.txt", "r");
    n_2 = input_data(data2_3, copy_flats2);
    fclose(data2_3);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_key(copy_flats2, n_2, keys2);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    for (int i = 0; i < n; i++)
    {
        keys2[i] = i;
    }

    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
    
    FILE *data2_4 = fopen("data_2.txt", "r");
    n_2 = input_data(data2_4, copy_flats2);
    fclose(data2_4);


    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_keys(copy_flats2, 0, n_2-1, keys2);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);







    flat_t copy_flats3[MAX_FLATS];

    FILE *data3_1 = fopen("data_3.txt", "r");
    int n_3 = input_data(data3_1, copy_flats3);
    fclose(data3_1);



    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_value(copy_flats3, n_3);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    FILE *data3_2 = fopen("data_3.txt", "r");
    n_3 = input_data(data3_2, copy_flats3);
    fclose(data3_2);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_value(copy_flats3, 0, n_3-1);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    int keys3[MAX_FLATS];

    for (int i = 0; i < n; i++)
    {
        keys3[i] = i;
    }


    FILE *data3_3 = fopen("data_3.txt", "r");
    n_3 = input_data(data3_3, copy_flats3);
    fclose(data3_3);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_key(copy_flats3, n_3, keys3);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    for (int i = 0; i < n; i++)
    {
        keys3[i] = i;
    }

    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
    
    FILE *data3_4 = fopen("data_3.txt", "r");
    n_3 = input_data(data3_4, copy_flats3);
    fclose(data3_4);


    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_keys(copy_flats3, 0, n_3-1, keys3);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);






    flat_t copy_flats4[MAX_FLATS];

    FILE *data4_1 = fopen("data_4.txt", "r");
    int n_4 = input_data(data4_1, copy_flats4);
    fclose(data4_1);



    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_value(copy_flats4, n_4);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    FILE *data4_2 = fopen("data_4.txt", "r");
    n_4 = input_data(data4_2, copy_flats4);
    fclose(data4_2);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_value(copy_flats4, 0, n_4-1);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    int keys4[MAX_FLATS];

    for (int i = 0; i < n; i++)
    {
        keys4[i] = i;
    }


    FILE *data4_3 = fopen("data_4.txt", "r");
    n_4 = input_data(data4_3, copy_flats4);
    fclose(data4_3);


    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;

    

    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        bubble_sort_for_key(copy_flats4, n_4, keys4);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);


    for (int i = 0; i < n; i++)
    {
        keys4[i] = i;
    }

    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
    
    FILE *data4_4 = fopen("data_4.txt", "r");
    n_4 = input_data(data4_4, copy_flats4);
    fclose(data4_4);


    for (int i = 0; i < REPEATS; i++)
    {

        times(&tmsBegin);
        quick_sort_for_keys(copy_flats4, 0, n_4-1, keys4);
        times(&tmsEnd);

        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;


        sum += elapsed_time;

        if (elapsed_time < min_time)
            min_time = elapsed_time;
        
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        
    }

    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);










    flat_t copy_flats5[MAX_FLATS + 1000];

    FILE *data5_1 = fopen("data_5.txt", "r");
    int n_5 = input_data(data5_1, copy_flats5);
    fclose(data5_1);
// 
// 
// 
    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
// 
    for (int i = 0; i < REPEATS; i++)
    {
// 
        times(&tmsBegin);
        bubble_sort_for_value(copy_flats5, n_5);
        times(&tmsEnd);
// 
        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;
// 
// 
        sum += elapsed_time;
// 
        if (elapsed_time < min_time)
            min_time = elapsed_time;
        // 
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        // 
    }
// 
    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);
// 
// 
    FILE *data5_2 = fopen("data_5.txt", "r");
    n_5 = input_data(data5_2, copy_flats5);
    fclose(data5_2);
// 
// 
    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
// 
    for (int i = 0; i < REPEATS; i++)
    {
// 
        times(&tmsBegin);
        quick_sort_for_value(copy_flats5, 0, n_5-1);
        times(&tmsEnd);
// 
        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;
// 
// 
        sum += elapsed_time;
// 
        if (elapsed_time < min_time)
            min_time = elapsed_time;
        // 
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        // 
    }
// 
    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);
// 
// 
    int keys5[MAX_FLATS];
// 
    for (int i = 0; i < n; i++)
    {
        keys5[i] = i;
    }
// 
// 
    FILE *data5_3 = fopen("data_5.txt", "r");
    n_5 = input_data(data5_3, copy_flats5);
    fclose(data5_3);
// 
// 
    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
// 
    // 
// 
    for (int i = 0; i < REPEATS; i++)
    {
// 
        times(&tmsBegin);
        bubble_sort_for_key(copy_flats5, n_5, keys5);
        times(&tmsEnd);
// 
        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;
// 
// 
        sum += elapsed_time;
// 
        if (elapsed_time < min_time)
            min_time = elapsed_time;
        // 
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        // 
    }
// 
    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);
// 
// 
    for (int i = 0; i < n; i++)
    {
        keys5[i] = i;
    }
// 
    max_time = -1, min_time = MAX_POSSIBLE_TIME, sum = 0;
    // 
    FILE *data5_4 = fopen("data_5.txt", "r");
    n_5 = input_data(data5_4, copy_flats5);
    fclose(data5_4);
// 
// 
    for (int i = 0; i < REPEATS; i++)
    {
// 
        times(&tmsBegin);
        quick_sort_for_keys(copy_flats5, 0, n_5-1, keys5);
        times(&tmsEnd);
// 
        elapsed_time = ((tmsEnd.tms_utime - tmsBegin.tms_utime) + 
                        (tmsEnd.tms_stime - tmsBegin.tms_stime)) * 1000000LL / CLOCKS_PER_SEC;
// 
// 
        sum += elapsed_time;
// 
        if (elapsed_time < min_time)
            min_time = elapsed_time;
        // 
        if (elapsed_time > max_time)
            max_time = elapsed_time;
        // 
    }
// 
    elapsed_times[j++] = (sum - max_time - min_time) / (REPEATS - 2);
}

// Вывод отсортированной таблицы с помощью ключей
void print_sorted_table_with_sorted_keys(flat_t flats[], int *n, int keys[])
{
    printf("\nКлючи    №          Адрес квартиры                        Площадь   Комнат  Цена за кв.м  Тип жилья   Отделка   Год постройки  Собственники  Жильцы  Животные\n\n");
    for (int i = 0; i < *n; i++)
    {

        printf("  %2d    %2d    ", keys[i]+1, i+1);
        if (flats[keys[i]].flat_type == SECONDARY)
        {
            printf("%40s     %3d        %d       %d         В          ---          %d         %d            %d       ",
            flats[keys[i]].address, flats[keys[i]].square, flats[keys[i]].room_amount, flats[keys[i]].price_per_meter, 
            flats[keys[i]].flat_info.secondary_t.build_year, flats[keys[i]].flat_info.secondary_t.owners_quantity, flats[keys[i]].flat_info.secondary_t.tenat_quantity);

            if (flats[keys[i]].flat_info.secondary_t.were_pet == YES_PET)
            {
                printf("да \n");
            }
            else
            {
                printf("нет \n");
            }   
        }


        if (flats[keys[i]].flat_type == PRIMARY)
        {
            printf("%40s     %3d        %d       %d         П          ", 
            flats[keys[i]].address, flats[keys[i]].square, flats[keys[i]].room_amount,  flats[keys[i]].price_per_meter);

            if (flats[keys[i]].flat_info.primary_t.repair == WITH_REPAIR)
            {
                printf("да           ---         ---          ---     ---\n");
            }
            else
            {
                printf("нет          ---         ---          ---     ---\n");
            }
        }
    }
}




int get_memory(int n)
{
    return 112 * n;
}

// Вывод таблицы сравнения сортировок и памяти
void print_comparing(double elapsed_time[], int size_flat, int size_keys, int n)
{
    int temp_n = n;

    printf("\nТаблица скорости работы сортировок. Kоличество повторов = 10000\n\n");
    printf("Количество записей                    Таблица ключей (ms)                         Исходная таблица (ms)\n\n");

    printf("                               Пузырьком                Быстрая                Пузырьком           Быстрая\n\n");

    for (int i = 1; i < 6; i++)
    {
        printf("     %3d                     %12.8f            %12.8f           %12.8f       %12.8f\n", temp_n, elapsed_time[0+(i-1)*4]*1000,
               elapsed_time[3 + (i-1)*4]*1000, elapsed_time[2 + (i-1)*4]*1000, elapsed_time[1+(i-1)*4]*1000);
        temp_n *= 2;
    }



    printf("\n\nТаблица занимаемой памяти в байтах\n\n");

    printf("   Количество записей             Таблица ключей            Исходная таблица\n\n");
    printf("         %3d                            %4d                        %5d\n", n, size_keys, size_flat);
    printf("         %3d                            %4d                        %5d\n", n*2, size_keys*2, size_flat*2);
    printf("         %3d                            %4d                        %5d\n", n*4, size_keys*4, size_flat*4);
    printf("         %3d                            %4d                        %5d\n", n*8, size_keys*8, size_flat*8);
    printf("         %3d                            %4d                        %5d\n\n", n*16, size_keys*16, size_flat*16);


    printf("Скорость сортировки массива ключей по сравнению с таблицей (сортировка пузырьком) быстрее в ~1.2 раза \n");
    printf("Скорость сортировки массива ключей по сравнению с таблицей (быстрая сортировка) быстрее в ~1.5 раза \n");
    printf("Память, используемая при сортировке массива ключей по сравнению с таблицей   больше в 28 раз\n\n");
}

int main_menu(flat_t flats[], int *n, int keys[])
{
    flat_t orig_flat[MAX_FLATS];
    int orig_n = *n;
    copy_flats(flats, *n, orig_flat);
    
    int choice = -1;
    while (choice != 0)
    {
        printf("\nВыберите действие: \n"
                "1 - Добавление записей\n"
                "2 - Удаление записей\n"
                "3 - Просмотр отсортированной таблицы ключей при несортированной исходной таблице\n"
                "4 - Вывод упорядоченной таблицы\n"
                "5 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей\n"
                "6 - Вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и таблице ключей\n"
                "7 - Поиск 2-х комнатных квартир во вторичном жилье без животных в указанном ценовом диапазоне\n"
                "8 - Вывод таблицы на экран\n"
                "0 - Выход\n\n");
        
        int rc = scanf("%d", &choice);

        if (rc != 1 || choice > 8 || choice < 0)
        {
            printf("Неверная команда\n");
            return ERROR_IN_CHOICE_DATA;
        }

        if (choice == 1)
        {
            int resp = add_flat_info();

            if (resp <= 0)
            {
                printf("Ошибка в количестве добавляемых квартир");
                return resp;
            }

            if (resp + *n > MAX_FLATS)
            {
                printf("Превышено количество записей\n");
                return OVERFLOW_ADD_FLATS;
            }

            for (int i = 0; i < resp; i++)
            {
                add_flat(flats, n);
                orig_flat[*n - 1] = flats[*n - 1];
                orig_n++;
            }
        }
        else if (choice == 2)
        {
            int response = delete_flat_info(flats, n, orig_flat, &orig_n);
            if (response != OK)
                return response;
        }
        else if (choice == 3)
        {
            quick_sort_for_keys(flats, 0, *n - 1, keys);
            print_sorted_table_keys(orig_flat, orig_n, keys);
        }
        else if (choice == 4)
        {
            flat_t temp_flat[MAX_FLATS];
            copy_flats(flats, *n, temp_flat);
            quick_sort_for_value(temp_flat, 0, *n-1);
            print_flats(temp_flat, *n);
        }
        else if (choice == 5)
        {
            quick_sort_for_keys(flats, 0, *n-1, keys);
            print_sorted_table_with_sorted_keys(orig_flat, &orig_n, keys);
        }
        else if (choice == 6)
        {

            double elapsed_times[100];

            counting_time(flats, *n, elapsed_times);
            int flats_size = get_memory(*n);
            int keys_size = *n * 4;

            print_comparing(elapsed_times, flats_size, keys_size, *n);
        }
        else if (choice == 7)
        {
            printf("Введите нижнюю границу ценового диапазона ");
            int low, high;
            int rc = scanf("%d", &low);

            if (rc != 1)
                return ERROR_IN_EDGE;
            
            printf("Введите верхнюю границу ценового диапазона ");
            rc = scanf("%d", &high);

            if (rc != 1)
                return ERROR_IN_EDGE;

            flat_t special_flats[MAX_FLATS];
            int n_spec = find_special_data(flats, *n, special_flats, low, high);

            if (n_spec == 0)
            {
                printf("\nНе найдены квартиры в указанном ценовом диапазоне\n");
                continue;
            }

            print_flats(special_flats, n_spec);        
        }
        else if (choice == 8)
        {
            print_flats(orig_flat, orig_n);
        }
    }

    return OK;
}   