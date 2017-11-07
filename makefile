CC=gcc
CFLAGS=-std=c99 -g
DEPS = shell.h
OBJ = shell.o finalmain.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minix: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
