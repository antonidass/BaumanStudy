CC := gcc

CFLAGS := -std=c99 -pedantic -Wvla -Wextra -g -Wvla -Werror

S := ./src/
O := ./out/

MK := mkdir -p


SRCS := $(wildcard $(S)*c)
OBJS := $(patsubst $(S)%.c,$(O)%.o,$(SRCS))	


app.out : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm


$(OBJS) : $(O)%.o : $(S)%.c
	$(MK) $(O); $(CC) $(CFLAGS) -c $< -o $@ -lm


.PHONY : clean r

r : 
	./app.out

clean :
	$(RM) $(O)*.o $(O)*.out $(O)*.exe

dot : 
	dot -Tpng tree.gv -otree.png && dot -Tpng balanced_tree.gv -obalanced_tree.png

