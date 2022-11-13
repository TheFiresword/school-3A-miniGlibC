OBJS	= mini_memory.o mini_io.o mini_string.o 
SOURCE	= src/mini_memory.c src/mini_io.c src/mini_string.c 
HEADER	= src/mini_lib.h
OUT= unitTesting  mini_shell mini_cat mini_clean mini_echo mini_grep mini_head mini_tail mini_touch wc mini_cp
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 


all: unitTesting  mini_shell clean 

unitTesting: $(OBJS) main.o
	$(CC) -g $(OBJS) main.o -o unitTesting  $(LFLAGS)

mini_touch:$(OBJS) mini_touch.o
	$(CC) -g $(OBJS) mini_touch.o -o mini_touch $(LFLAGS)

mini_echo:$(OBJS) mini_echo.o
	$(CC) -g $(OBJS) mini_echo.o -o mini_echo $(LFLAGS)

mini_cat:$(OBJS) mini_cat.o
	$(CC) -g $(OBJS) mini_cat.o -o mini_cat $(LFLAGS)

mini_head:$(OBJS) mini_head.o
	$(CC) -g $(OBJS) mini_head.o -o mini_head $(LFLAGS)

mini_tail:$(OBJS) mini_tail.o
	$(CC) -g $(OBJS) mini_tail.o -o mini_tail $(LFLAGS)

mini_clean:$(OBJS) mini_clean.o
	$(CC) -g $(OBJS) mini_clean.o -o mini_clean $(LFLAGS)

mini_grep:$(OBJS) mini_grep.o
	$(CC) -g $(OBJS) mini_grep.o -o mini_grep $(LFLAGS)

mini_cp:$(OBJS) mini_cp.o
	$(CC) -g $(OBJS) mini_cp.o -o mini_cp $(LFLAGS)

wc:$(OBJS) wc.o
	$(CC) -g $(OBJS) wc.o -o wc $(LFLAGS)

mini_shell:$(OBJS) mini_shell.o mini_cat mini_clean mini_echo mini_grep mini_head mini_tail mini_touch wc mini_cp readlinelib
	$(CC) -g $(OBJS) mini_shell.o -lreadline -o mini_shell $(LFLAGS)

mini_memory.o: src/mini_memory.c
	$(CC) $(FLAGS) src/mini_memory.c 

mini_io.o: src/mini_io.c
	$(CC) $(FLAGS) src/mini_io.c 

mini_string.o: src/mini_string.c
	$(CC) $(FLAGS) src/mini_string.c

mini_shell.o: src/mini_shell.c
	$(CC) $(FLAGS) src/mini_shell.c

mini_cat.o: src/mini_cat.c
	$(CC) $(FLAGS) src/mini_cat.c

mini_touch.o: src/mini_touch.c
	$(CC) $(FLAGS) src/mini_touch.c

mini_echo.o: src/mini_echo.c
	$(CC) $(FLAGS) src/mini_echo.c

mini_head.o: src/mini_head.c
	$(CC) $(FLAGS) src/mini_head.c

mini_tail.o: src/mini_tail.c
	$(CC) $(FLAGS) src/mini_tail.c

mini_clean.o: src/mini_clean.c
	$(CC) $(FLAGS) src/mini_clean.c

mini_grep.o: src/mini_grep.c
	$(CC) $(FLAGS) src/mini_grep.c

mini_cp.o: src/mini_cp.c
	$(CC) $(FLAGS) src/mini_cp.c

wc.o: src/wc.c
	$(CC) $(FLAGS) src/wc.c

main.o: src/main.c
	$(CC) $(FLAGS) src/main.c 

readlinelib:
	sudo apt-get install libreadline-dev
	
mr_proper:clean
	rm -f $(OUT)

clean:
	rm -f $(OBJS) mini_touch.o mini_echo.o mini_cat.o mini_head.o mini_tail.o mini_clean.o mini_grep.o wc.o main.o mini_shell.o mini_cp.o