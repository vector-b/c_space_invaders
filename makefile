objects = jogo.o
# regras de compilação
jogo.o: main.c 
	gcc -o jogo main.c lista.c space.c  -lncurses -g 
