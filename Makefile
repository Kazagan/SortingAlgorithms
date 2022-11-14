CLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lm

main:
	$(CC) $(CFLAGS) -o ./sortingAlgorithms ./start.c $(LIBS) ./sort.c
