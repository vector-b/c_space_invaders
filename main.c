#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "space.h"
int main()
{
	int nlin,ncol;
	int cont = 0;
	int right = 1;
	int changed = 0;
	int i,j;

	/* Inicialização dos recursos ncurses */
	initscr();				
	clear();	
	refresh();
	getmaxyx(stdscr, nlin, ncol);
	cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */

	/*Inicia a lista dinamica usada para os objetos do jogo */
	lista *obj; 
	obj = malloc(sizeof(obj));
	if (!inicia_lista(obj))
	{
		printf("Memória Indisponivel\n");
		exit(1);
	}
    /*Criação e inicialização do mapa */
	mapa *map;
	map = malloc(sizeof(map));
	map = geramapa(map,nlin,ncol);

	/*Criação e inicialização da placa(que faz a movimentação dos aliens)*/
	placa_a *placa;
	placa = malloc(sizeof(placa));
	placa = inicializa_placa(obj,map,placa, nlin, ncol);


	/*Criação e inicialização do canhão*/
	insere_inicio_lista(1,(nlin - 4), (ncol/2)-5,5,1,obj);
	obj = inicia_canhao(obj,map);

	if (right)
		deletecolumn(map,placa,&right);
	while (1/*ganhou, perdeu ou apertou esc*/)
	{
		if (map -> data[(placa -> linha)+ (placa -> altura)][(placa -> coluna) + (placa -> largura)] == '|')
		{
			right = 0;
			changed = 1;
			deletetop(map,placa);
			deletecolumn(map,placa,&right);
		}
		else if (map -> data[(placa -> linha) -1 ][(placa -> coluna) - 1] == '|')
		{
			right = 1;
			changed = 1;
			deletetop(map,placa);
			deletecolumn(map,placa,&right);
		}
		entra_tiro(map,placa);

		busca_tiro(map);

		sai_tiro(map, placa);

		busca_tiro_placa(placa,right, &changed);

		refresh();

		usleep(100000);

		clear();
		if (right)
			placa -> coluna++;
		else
			placa -> coluna--;

		ande_alien(map,placa);
		
		if (right)
			deletecolumn(map,placa,&right);
		else
			deletecolumn(map,placa,&right);
		switch(getch()) {
    		case 'd':
    		{
    			obj -> begin -> col++;
        		break;
    		}
    		case 'a':
    		{
    			obj -> begin -> col--;
        		break;
    		}
    		case 'p':
    		{
    			atirar(obj -> begin,map);
        		break;
    		}

		}	
		imprime_canhao(obj -> begin ,map);
		for (i = 0; i <  (map -> linhas); i++)
		{
			for (j = 0; j < (map -> colunas); j++)
				printw("%c", map -> data[i][j]);
			printw("\n");
		}
		cont++;
	}

	getch();
 	endwin();
	return 0;
}