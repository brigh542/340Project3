CC=gcc
CFLAGS=-std=c99 -g
DEPS = minix.h
OBJ = help.o main.o minix.o showsuper.o traverse.o showzone.o quit.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minix: $(OBJ)
gcc -o $@ $^ $(CFLAGS)
