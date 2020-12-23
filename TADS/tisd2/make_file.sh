#usr/bin/bash
echo 'Компиляция файла...'
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion sorts.c iostream.c main.c

