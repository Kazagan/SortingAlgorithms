LAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lm

main:
	$(CC) $(CFLAGS) -o ./build/$1 $1.c $(LIBS)
