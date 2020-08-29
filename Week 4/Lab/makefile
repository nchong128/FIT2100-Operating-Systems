OBJS = main.o arithmetic.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall

ilovemaths.o: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ilovemaths.o

main.o: main.c arithmetic.h
	$(CC) $(CFLAGS) main.c -o main.o

arithmetic.o: arithmetic.c arithmetic.h
	$(CC) $(CFLAGS) arithmetic.c -o arithmetic.o