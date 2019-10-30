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
	mapa *map;
	map = geramapa(map,nlin,ncol);
	placa_a *placa;
	placa = inicializa_placa(map,placa, nlin, ncol);
	if (right)
		deletecolumn(map,placa,&right);
	while (cont < 100)
	{
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
		{
			/* limpa_cima*/
			placa -> coluna--;
		}
		ande_alien(map,placa);
		if (right)
			deletecolumn(map,placa,&right);
		else
			deletecolumn(map,placa,&right);

		for (i = 0; i <  (map -> linhas); i++)
		{
			for (j = 0; j < (map -> colunas); j++)
				printw("%c", map -> data[i][j]);
			printw("\n");
		}
		cont++;
	}
	/*while(cont < 4)
	{
		sleep(2);
		clear();
		refresh();
		
		
	}

	*/
	getch();
 	endwin();

 	/*mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);*/
	return 0;
}