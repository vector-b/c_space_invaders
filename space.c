#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


mapa *geramapa(mapa *m, int nlin, int ncol)
{
	int i,j,k;
	m = malloc(sizeof(m));
	m ->  linhas = nlin;
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



	return m;
}
placa_a *inicializa_placa(mapa *m, placa_a *p, int linIni, int colIni)
{
	p = malloc(sizeof(p));
	p -> linha = 6;
	p -> coluna = 4;
	p -> altura = linIni*0.60;
	p -> largura = colIni*0.90;
	int i,k;
	p -> data = malloc(p -> altura * sizeof(p -> data));
	for (i = 0; i < p -> altura; i++)
	{
		p -> data[i] = malloc(p -> largura*sizeof(p -> data[i]));
	}

	for (i = 0; i < (p -> altura); i++)
		for (k = 0; k < (p -> largura); k++)
		{
			p -> data[i][k] = '+';
		}
	return p;
}
void ande_alien(mapa *m, placa_a *p)
{
	int i,k;
	for (i = 0; i < p -> altura; i++)
	{
		for (k = 0; k < p -> largura; k++)
		{
			m -> data[i + (p -> linha)][k + (p -> coluna)] = p -> data[i][k]; 
		}
	}
}
void deletecolumn(mapa *m, placa_a *p, int *right)
{
	int i;
	if (*right)
	{
		for (i = 0; i < p -> altura; i++)
			m -> data[p -> linha + i][p -> coluna] = ' ';
	}
	else
	{
		for (i = 0; i < p -> altura; i++)
			m -> data[p -> linha + i][p -> coluna + p-> largura -1] = ' ';
	}
	
}
void deletetop(mapa *m, placa_a *p)
{
	int i,k;
	p -> linha++;
	for (i = 0; i < p -> altura; i++)
	{
		for (k = 0; k < p -> largura; k++)
		{
			m -> data[i + (p -> linha)][k + (p -> coluna)] = p -> data[i][k]; 
		}
	}
	for (i = 0; i < p -> largura; i++)
		m -> data[p -> linha - 1][p -> coluna + i] = ' ';
	
}
