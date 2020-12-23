#usr/bin/bash
echo 'Компиляция файла...'
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion functions.c iostream.c main.c

