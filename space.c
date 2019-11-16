#include "space.h"
#include <stdlib.h>
#include <stdio.h>

mapa *inicia_mapa(mapa *m, int lin, int col)
{
	m = malloc(sizeof(m));
	m -> linhas = lin;
	m -> colunas = col - 1;
	int i,j,k;
	m -> data = malloc(lin * sizeof(m));
	for (i = 0; i < lin; i++)
		m -> data[i] = malloc((col - 1)  * sizeof(m));

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

placa_a *inicia_placa(t_lista *l,placa_a *p, int lin, int col)
{
	p = malloc(sizeof(p));
	p -> linha = 6;
	p -> coluna = 4;
	p -> altura = lin*0.40;
	p -> largura = col*0.40;
	int i,k;
	p -> data = malloc(p -> altura * sizeof(p -> data));
	for (i = 0; i < p -> altura; i++)
	{
		p -> data[i] = malloc(p -> largura*sizeof(p -> data[i]));
	}

	for (i = 0; i < p -> altura; i++)
	{
		p -> data[i][0] = '*';
		p -> data[i][p -> largura - 1] = '*';
	}
	for (i = 0; i < p -> largura; i++)
	{
		p -> data[0][i] = '*';
		p -> data[p -> altura - 1][i] = '*';
	}
	for (i = 1; i < p -> altura-1; i++)
	{
		for (k = 1; k < p -> largura-1; k++)
		{
			p -> data[i][k] = ' ';
		}
	}

	for (i = 2; i < p -> largura - 3; i+= 12)
	{
		gera_alien(l,p,1,i,1);
	}
		
	for (i = 1; i < p -> largura - 5 ; i+= 15)
	{
		gera_alien(l,p,6,i,2);
	}
	return p;
}

void *inicia_canhao(t_lista *l, mapa *m)
{
	int i,k;
	t_nodo *canhao;
	canhao = l -> begin;

	canhao -> data = malloc(2 *sizeof(canhao -> data));
	for (i = 0; i < 2; i++)
	{
		canhao -> data[i] = malloc(5 * sizeof(canhao -> data[i]));
	}
	canhao -> data[0][0] = ' ';
	canhao -> data[0][1] = '/';
	canhao -> data[0][2] = '^';
	canhao -> data[0][3] = '\\';
	canhao -> data[0][4] = ' ';
	canhao -> data[1][0] = '=';
	canhao -> data[1][1] = '=';
	canhao -> data[1][2] = '=';
	canhao -> data[1][3] = '=';
	canhao -> data[1][4] = '=';
	for (i = 0; i < 2; i++)
	{	
		for (k = 0; k < 5; k++)
		{
			m -> data[canhao -> lin + i][canhao -> col + k] = canhao -> data[i][k]; 
		}
	}
}
void gera_alien(t_lista *l,placa_a *p, int linIni,int colIni, int tipo)
{
	if (tipo == 1)
	{
		p -> data[linIni][colIni+1] = 'A';
		p -> data[linIni+1][colIni] = 'A';
		p -> data[linIni+1][colIni+1] = 'M';
		p -> data[linIni+1][colIni+2] = 'A';
		p -> data[linIni+2][colIni] = '/';
		p -> data[linIni+2][colIni+1] = 'X';
		p -> data[linIni+2][colIni+2] = '\\';
		insere_fim_lista(tipo + 1,linIni,colIni,3,3,1,l);
	}
	else if (tipo == 2)
	{
		p -> data[linIni][colIni] = '.';
		p -> data[linIni][colIni+1] = 'v';
		p -> data[linIni][colIni+2] = '_';
		p -> data[linIni][colIni+3] = 'v';
		p -> data[linIni][colIni+4] = '.';
		p -> data[linIni+1][colIni] = '}';
		p -> data[linIni+1][colIni+1] = 'W';
		p -> data[linIni+1][colIni+2] = 'M';
		p -> data[linIni+1][colIni+3] = 'W';
		p -> data[linIni+1][colIni+4] = '{';
		p -> data[linIni+2][colIni+1] = '/';
		p -> data[linIni+2][colIni+2] = ' ';
		p -> data[linIni+2][colIni+3] = '\\';
		insere_fim_lista(tipo + 1,linIni,colIni,5,5,1,l);
	}
	else if (tipo == 3)
	{
		p -> data[linIni][colIni] = ' ';
		p -> data[linIni][colIni+1] = 'n';
		p -> data[linIni][colIni+2] = 'm';
		p -> data[linIni][colIni+3] = 'n';
		p -> data[linIni][colIni+4] = ' ';
		p -> data[linIni+1][colIni] = 'd';
		p -> data[linIni+1][colIni+1] = 'b';
		p -> data[linIni+1][colIni+2] = 'M';
		p -> data[linIni+1][colIni+3] = 'd';
		p -> data[linIni+1][colIni+4] = 'b';
		p -> data[linIni+2][colIni] = '_';
		p -> data[linIni+2][colIni+1] = '/';
		p -> data[linIni+2][colIni+2] = '-';
		p -> data[linIni+2][colIni+3] = '\\';
		p -> data[linIni+2][colIni+4] = '_';
		insere_fim_lista(tipo + 1,linIni,colIni,5,5,1,l);
	}
}
void transicao(mapa *m, placa_a *p)
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
void atirar(t_nodo *n,mapa *m)
{
	m -> data[ n -> lin -1][n -> col+2] = '|';
}
void busca_tiro(mapa *m)
{
	int i,k;
	for (i = 2; i <  m -> linhas - 2; i++)
	{
		for (k = 2; k < m -> colunas - 2; k++)
		{
			if (m -> data[i][k] == '|')
			{
				m -> data[i-1][k] = '|';
				m -> data[i][k] = ' ';
			}
		}
	}
}
void entra_tiro(mapa *m, placa_a *p)
{
	int i;
	for (i = 0; i < p -> largura; i++)
	{
		if (m -> data[p -> linha + p -> altura][p -> coluna + i] == '|')
			p -> data[p->altura-1][i] = '|';
	}
}
void sai_tiro(mapa *m, placa_a *p)
{
	int i;
	for (i = 0; i < p -> largura; i++)
	{
		if (p -> data[0][i] == '|')
		{
			m -> data[p -> linha - 1][p -> coluna + i ] = '|';
			p -> data[0][i] = ' ';
		}

	}
}
void busca_tiro_placa(placa_a *p, int dir, int *changed)
{
	int i,k;
	for (i = 1; i <  p -> altura ; i++)
	{
		for (k = 1; k < p ->  largura; k++)
		{
			if (p -> data[i][k] == '|')
			{
				if (*changed == 0)
				{
					if (dir)
						p -> data[i-1][k-1] = '|';
					else
						p -> data[i-1][k+1] = '|';
					p -> data[i][k] = ' ';

				}	
				else
				{
					if (dir)
						p -> data[i-1][k+1] = '|';
					else
						p -> data[i-1][k-1] = '|';
					p -> data[i][k] = ' ';
					*changed = 0;
				}
				
			}
		}
	}
}
void imprime_canhao(t_nodo *n, mapa *m)
{
	int i,k;
	for (i = 0; i < 5; i++)
	{
		n -> data[1][i] = '=';
	}
	for (i = 0; i < 2; i++)
	{	
		for (k = 0; k < 5; k++)
		{
			m -> data[n -> lin + i][n -> col + k] = n -> data[i][k];
			if (k == 0)
				m -> data [n -> lin + i][n -> col + k - 1] = ' ';
			else if (k == 4)
				m -> data [n -> lin + i][n -> col + k + 1] = ' ';  
		}
	}	
}
void atinge_alien(t_lista *l, placa_a *p)
{
	int i;
	t_nodo *n;
	n = l -> begin;
	while (n != NULL)
	{
		if (n -> type >= 2 && n -> type <= 3)
		{
			for (i = n -> col; i < n -> col + n -> larg - 1; i++)
			{
				if (p -> data[n -> lin + n -> alt - 1 ][i] == '|')
				{ 
					n -> state = 0;
					p -> data[n -> lin + n -> alt - 1 ][i] = ' ';
					busca_e_remove(l,p);
					printf("aaa\n");
				}
			}
		}
		n = n -> next;
	} 
}
void busca_e_remove(t_lista *l, placa_a *p)
{
	t_nodo *n;
	int i,k;
	n = l -> begin;
	while (n != NULL)
	{
		if (n -> type >= 2 && n -> type <= 3)
		{
			if (n -> state == 0)
			{
				for (i = n -> lin ; i < n -> lin + n -> larg ; i++)
				{
					for (k = n -> col; k < n -> col + n -> alt  ; k++)
					{
						p -> data[i][k] = ' ';
					}
				}
			}
			//remove_nodo(tal)
		}
		n = n -> next;
	}
}