CC=gcc
CFLAGS=-std=c99 -g
DEPS = shell.h
OBJ = shell.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minix: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
