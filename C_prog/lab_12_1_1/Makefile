CC := gcc

CFLAGS := -std=c99 -pedantic -Wvla -Wextra -Wall -Werror
UFLAGS := -std=c99 -Wall -Werror -pedantic -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -lcheck

S := ./static_lib/
D1 := ./dynamic1_lib/
D2 := ./dynamic2_lib/
U := ./unit_tests/


TEST_OBJS := $(U)check_main.o $(U)check_functions.o


unit_tests.exe : $(TEST_OBJS) $(S)functions.o $(S)iostream.o
	$(CC) -o $@ $^ $(UFLAGS)



all : $(S)app_static.exe $(D1)app_dynamic_1.exe $(D2)app_dynamic_2.exe

SSRC := $(wildcard $(S)*c)
SOBJS := $(patsubst $(S)%.c, $(S)%.o, $(SSRC))
SLIB_NAMES := $(S)iolib.a $(S)funclib.a




$(S)app_static.exe : $(S)main.c $(SLIB_NAMES)
	$(CC) $(CFLAGS) $^ -o $@

$(S)iolib.a : $(S)iostream.o
	ar rc $@ $^

$(S)funclib.a : $(S)functions.o
	ar rc $@ $^

$(SOBJS) : $(S)%.o : $(S)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJS) : $(U)%.o : $(U)%.c
	$(CC) $(UFLAGS) -c $< -o $@





D1SRC := $(wildcard $(D1)*c)
D1OBJS := $(patsubst $(D1)%.c, $(D1)%.o, $(D1SRC))
D1LIB_NAMES := $(D1)iolib.dll $(D1)funclib.dll

$(D1)app_dynamic_1.exe : $(D1)main.c $(D1LIB_NAMES)
	$(CC) $(CFLAGS) $^ -o $@


$(D1)iolib.dll : $(D1)iostream.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

$(D1)funclib.dll : $(D1)functions.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

$(D1OBJS) : $(D1)%.o : $(D1)%.c
	$(CC) $(CFLAGS) -c $< -o $@



D2SRC := $(wildcard $(D2)*c)
D2OBJS := $(patsubst $(D2)%.c, $(D2)%.o, $(D2SRC))
D2LIB_NAMES := $(D2)iolib2.dll $(D2)funclib2.dll

$(D2)app_dynamic_2.exe : $(D2)main.c $(D2LIB_NAMES)
	$(CC) $(CFLAGS) $^ -o $@

$(D2)iolib2.dll : $(D2)iostream.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

$(D2)funclib2.dll : $(D2)functions.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

$(D2)functions.o : $(D2)functions.c
	$(CC) $(CFLAGS) -D FUNC_EXPORTS -c $< -o $@

$(D2)iostream.o : $(D2)iostream.c
	$(CC) $(CFLAGS) -D IO_EXPORTS -c $< -o $@



	

.PHONY : clean unit stc dyn1 dyn2


stc :
	$(S)app_static.exe data1.txt out.txt f

dyn1 :
	$(D1)app_dynamic_1.exe data1.txt out.txt f

dyn2 :
	$(D2)app_dynamic_2.exe data1.txt out.txt f


clean : 
	$(RM) $(S)*.o $(S)*.a $(D1)*.dll $(D1)*.o $(D2)*.dll $(D2)*.o $(S)*.exe $(D1)*.exe $(D2)*.exe $(U)*.o