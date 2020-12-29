CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic
UFLAGS := -lcheck

S := ./src/
O := ./out/
U := ./unit_tests/
H := ./inc/

MK := mkdir -p ./out

OBJS := $(O)functions.o $(O)iostream.o $(O)main.o
TEST_OBJS := $(O)check_main.o $(O)check_sort.o $(O)check_filter.o $(O)check_iostream.o


app.exe : $(OBJS)
	$(MK)
	$(CC) $^ -o $@

unit_tests.exe : $(O)functions.o $(O)iostream.o $(TEST_OBJS) 
	$(MK)
	$(CC) -o $@ $^ $(UFLAGS)



$(O)check_main.o : $(U)check_main.c $(U)check_filter.c $(U)check_iostream.c $(U)check_sort.c
	$(MK)
	$(CC) $(UFLAGS) -c $< -o $@

$(O)check_sort.o : $(U)check_sort.c
	$(MK)
	$(CC) $(UFLAGS) -c $< -o $@	

$(O)check_filter.o : $(U)check_filter.c
	$(MK)
	$(CC) $(UFLAGS) -c $< -o $@	

$(O)check_iostream.o : $(U)check_iostream.c
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



.PHONY : clean


clean :
	$(RM) $(O)*.o $(O)*.out $(O)*.exe
	$(RM) *.exe -rf ./out
