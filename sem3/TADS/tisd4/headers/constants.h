#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#ifndef CONSTANTS
#define CONSTANTS


#define OK 0
#define MAX_STACK_SIZE 1000000

#define ERROR_IN_CHOICE -1
#define ERROR_IN_INPUT_DATA -2
#define STACK_OVERFLOW -3
#define ERROR_IN_CAPACITY_CHOICE -4
#define EMPTY_STACK -500
#define ERROR_IN_ADD_ELEMS -5
#define ERROR_IN_DELETE_ELEMS -6
#define NO_ELEMENTS_FOR_DELETE -7

#define NO_ELEMS_FOR_PRINT_MSG "Нельзя вывести элементы так как стек пуст\n"
#define ERROR_IN_CHOICE_MSG "Ошибка в выборе команды\n"
#define ERROR_IN_INPUT_DATA_MSG "Введены неккоректные данные!\n" 
#define STACK_OVERFLOW_MSG "Невозможно добавить элемент в стек, так как стек переполнен\n"
#define ERROR_IN_CAPACITY_CHOICE_MSG "Ошибка в размере стека!\n"
#define EMPTY_STACK_MSG "Невозможно удалить элемент из стека, так как стек пуст!\n"
#define ERROR_IN_ADD_ELEMS_MSG "Неверное количество добавляемых элементов\n"
#define ERROR_IN_DELETE_ELEMS_MSG "Неверное количество удаляемых элементов\n"
#define NO_ELEMENTS_FOR_DELETE_MSG "Невозможно удалить элементы из стека так как стек пуст\n"

#endif