CLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lm

main:
	$(CC) $(CFLAGS) -o $1 $1.c $(LIBS)
	mv $1 ./build/
