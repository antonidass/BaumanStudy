CC := gcc

CFLAGS := -std=c99 -pedantic -Wvla -Wextra -Wall -Werror
UFLAGS := -std=c99 -Wall -Werror -pedantic -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -lcheck


D2 := ./my_lib/
U := ./unit_tests/

TEST_OBJS := $(U)check_main.o $(U)check_functions.o



unit_tests.exe : $(TEST_OBJS) $(D2)my_lib.o
	$(CC) -o $@ $^ $(UFLAGS)

build : mylib.so

mylib.so : $(D2)my_lib.o
	$(CC) -o $@ -shared $^

$(D2)my_lib.o : $(D2)my_lib.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@


.PHONY : clean unit run


run : 
	python3 main.py

clean :
	$(RM) $(D2)*.o *.so

unit :
	./unit_tests.exe
