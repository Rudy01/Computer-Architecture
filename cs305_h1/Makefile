CC = gcc
CFLAGS = -g -Wall --std=c11
OBJECTS = main.o
all: a.out
a.out: main.o
	$(CC) $(CFLAGS) -o a.out main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm a.out main.o *~
