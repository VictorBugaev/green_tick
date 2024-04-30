CC=gcc
SRC=my_grep.c
CFLAGS=-Wall -Werror -Wextra


all: my_grep clean

my_grep: my_grep.o
		$(CC) $(CFLAGS) $^ -o my_grep

my_grep.o: $(SRC)
		$(CC) $(CFLAGS) -c $^

clean:
		rm -rf *.o
