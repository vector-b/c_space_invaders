OBJS =  main.c
TARG = space_invaders 
CFLAG = -Wall 
CC = gcc
INCLUDE = lista.c fila.c space.c
LIBS = -lncurses

hello:${OBJS}
	${CC} -o  ${TARG} ${OBJS} ${INCLUDE} ${LIBS} ${CFLAG}

clean:
	-rm -f *.o space_invaders