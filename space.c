#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


mapa *geramapa(mapa *m, int nlin, int ncol)
{
	int i,j,k;
	m = malloc(sizeof(m));
	m ->  linhas = nlin-1;
	m -> colunas = ncol-1;

	m -> data = malloc(m -> linhas*sizeof(m));

	
	for (i = 0; i < m -> linhas; i++)
		m -> data[i] = malloc(m -> colunas*sizeof(m));

	for (i = 0; i <  m -> linhas; i++)
		for (j = 0; j < m ->  colunas; j++)
			m -> data[i][j] = ' ';

	/*border top-bottom*/
	for (k = 0; k < m -> colunas; k++)
	{
		m -> data[0][k] = '-';
		m -> data[(m -> linhas) - 1][k] = '-';
	}
	/*border right-left*/
	for (k = 1; k < m -> linhas -1 ; k++)
	{
		m -> data[k][0] = '|';
		m -> data[k][(m -> colunas) - 1] = '|';
	}

	for (i = 0; i <  m -> linhas; i++)
	{
		for (j = 0; j < m ->  colunas; j++)
			printw("%c", m -> data[i][j] );
		printw("\n");
	}		

	return m;
}