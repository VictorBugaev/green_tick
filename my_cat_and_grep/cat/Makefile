CC=gcc
SRC=my_cat.c
CFLAGS=-Wall -Werror -Wextra


all: my_cat clean

my_cat: my_cat.o
		$(CC) $(CFLAGS) $^ -o my_cat

my_cat.o: $(SRC)
		$(CC) $(CFLAGS) -c $^

clean:
		rm -rf *.o 