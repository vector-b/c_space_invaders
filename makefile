objects = jogo.o
# regras de compilação
jogo.o: main.c 
	gcc -o jogo main.c lista.c fila.c space.c -Wall -ansi  -lncurses -g 
