CC = gcc
CFLAGS = -g -Wall --std=c11 -o -Werror
OBJECTS = main.o
all: a.out
a.out: main.o
	$(CC) $(CFLAGS) -o a.out $(OBJECTS)
main.o: main.c main.h
	$(CC)  $(CFLAGS) -c main.c -o main.o
clean:
	rm $(OBJECTS) a.out *~
