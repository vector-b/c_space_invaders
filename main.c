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
	int i,j;
	initscr();				
	clear();	
	refresh();
	getmaxyx(stdscr, nlin, ncol);
	cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */
	mapa *map;
	map = geramapa(map,nlin,ncol);
	placa_a *placa;
	placa = inicializa_placa(map,placa, nlin, ncol);
	canhao *c;
	c = inicia_canhao(c,map,(nlin - 4), (ncol/2)-5);
	if (right)
		deletecolumn(map,placa,&right);
	while (cont < 100)
	{
		entra_tiro(map,placa);
		busca_tiro(map);
		busca_tiro_placa(placa);
		sai_tiro(map, placa);

		if (map -> data[(placa -> linha)+ (placa -> altura)][(placa -> coluna) + (placa -> largura)] == '|')
		{
			right = 0;
			deletetop(map,placa);
			deletecolumn(map,placa,&right);
		}
		else if (map -> data[(placa -> linha) -1 ][(placa -> coluna) - 1] == '|')
		{
			right = 1;
			deletetop(map,placa);
			deletecolumn(map,placa,&right);
		}

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
    			c -> coluna++;
        		break;
    		}
    		case 'a':
    		{
    			c -> coluna--;
        		break;
    		}
    		case 'p':
    		{
    			atirar(c,map);
        		break;
    		}

		}	
		imprime_canhao(c,map);
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

 	/*mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);*/
	return 0;
}