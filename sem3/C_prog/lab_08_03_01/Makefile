CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic
UFLAGS := -std=c99 -Wall -Werror -pedantic -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -lcheck 

S := ./src/
O := ./out/
U := ./unit_tests/
H := ./headers/

MK := mkdir -p ./out

OBJS := $(O)functions.o $(O)iostream.o $(O)main.o
TEST_OBJS := $(O)check_main.o $(O)check_functions.o


app.exe : $(OBJS)
	$(MK)
	$(CC) $^ -o $@

unit_tests.exe : $(O)functions.o $(O)iostream.o $(TEST_OBJS) 
	$(MK)
	$(CC) -o $@ $^ $(UFLAGS)



$(O)check_main.o : $(U)check_main.c $(U)check_functions.c 
	$(MK)
	$(CC) $(UFLAGS) -c $< -o $@

$(O)check_functions.o : $(U)check_functions.c
	$(MK)
	$(CC) $(UFLAGS) -c $< -o $@	

$(O)main.o : $(S)main.c $(S)functions.c $(S)iostream.c $(H)*.h
	$(MK)
	$(CC) $(CFLAGS) -c $< -o $@

$(O)functions.o : $(S)functions.c $(H)functions.h
	$(MK)
	$(CC) $(CFLAGS) -c $< -o $@

$(O)iostream.o : $(S)iostream.c $(H)iostream.h
	$(MK)
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY : clean start unit

clean :
	$(RM) $(O)*.o $(O)*.out $(O)*.exe
	$(RM) *.exe -rf ./out

start :
	./app.exe < in2.txt

unit :
	./unit_tests.exe