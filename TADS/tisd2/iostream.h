#pragma once
#include "constants.h"
#include "data_structures.h"
#include "sorts.h"



void read_line(char temp_line[], int *i, char data_in_line[]);
int input_data(FILE *data_file, flat_t flats[]);
int find_special_data(flat_t flats[], int n_flats, flat_t special_flats[], int low_price_border, int high_price_border);
void print_flats(const flat_t flats[], int n_flats);
int add_flat(flat_t flats[], int *n_flats);
void delete_flat(flat_t flats[], int *n_flats, int num);
int delete_flat_info(flat_t flats[], int *n_flats, flat_t orig_flats[], int *orig_n);
int add_flat_info();
void copy_flats(flat_t flats_origin[], int n, flat_t flats_destination[]);
void print_sorted_table_keys(flat_t flats[], int n, int keys[]);
void counting_time(flat_t flats[], int n, double elapsed_times[]);
void print_sorted_table_with_sorted_keys(flat_t flats[], int *n, int keys[]);
int get_memory(int n);
void print_comparing(double elapsed_time[], int size_flat, int size_keys, int n);
int main_menu(flat_t flats[], int *n, int keys[]);