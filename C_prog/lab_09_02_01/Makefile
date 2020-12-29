CC := gcc

CFLAGS := -std=c99 -pedantic -Wvla -Wextra -Wall -Werror
UFLAGS := -std=c99 -Wall -Werror -pedantic -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -lcheck 


S := ./src/
O := ./out/
U := ./unit_tests/

MK := mkdir -p


SRCS := $(wildcard $(S)*c)
OBJS := $(patsubst $(S)%.c,$(O)%.o,$(SRCS))	
TEST_OBJS := $(O)check_main.o $(O)check_functions.o $(O)check_iostream.o
SRC_OBJS := $(O)functions.o $(O)iostream.o


app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

unit_tests.exe : $(TEST_OBJS) $(SRC_OBJS)
	$(CC) -o $@ $^ $(UFLAGS)



$(OBJS) : $(O)%.o : $(S)%.c
	$(MK) $(O); $(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJS) : $(O)%.o : $(U)%.c
	$(MK) $(O); $(CC) $(UFLAGS) -c $< -o $@



.PHONY : clean run unit

run : 
	./app.exe data.txt 

clean :
	$(RM) $(O)*.o $(O)*.out *.exe $(O)*.exe

unit :
	./unit_tests.exe