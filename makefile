CC=gcc
CFLAGS=-Wall -ansi
DEPS = space.c lista.c fila.c
OBJ = space_invaders.o  

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

space_invaders: $(OBJ)
	$(CC) -o $(DEPS) $(CFLAGS)