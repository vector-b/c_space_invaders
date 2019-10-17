#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "space.h"
int main()
{
	int nlin,ncol;
	initscr();				
	clear();	
	refresh();
	getmaxyx(stdscr, nlin, ncol);
	mapa *map;
	map = geramapa(map,nlin,ncol);
	placa *placa;
	placa = inicializa_placa(placa,map, 4, 2);
	/*//mvprintw(map -> linhas, map -> colunas, "%s", map -> data);*/
	int cont = 0;
	while(cont++ < 4)
	{
		andaralienigiena(map);
	}
	getch();
 	endwin();

 	/*mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);*/
	return 0;
}