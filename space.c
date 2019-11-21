#include "space.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
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
	for (k = 5; k < m -> linhas -1 ; k++)
	{
		m -> data[k][0] = '|';
		m -> data[k][(m -> colunas) - 1] = '|';
	}
	return m;
}

placa_a *inicia_placa(t_lista *l,placa_a *p, int lin, int col)
{
	p = malloc(86*sizeof(p));
	p -> linha = 6;
	p -> coluna = 4;
	p -> altura = 19;
	p -> largura = col*0.45;
	p -> numero_aliens = 0;
	int i,k;
	p -> data = malloc(p -> altura * sizeof(p -> data));
	for (i = 0; i < p -> altura; i++)
	{
		p -> data[i] = malloc(p -> largura*sizeof(p -> data[i]));
	}

	for (i = 0; i < p -> altura; i++)
	{
		p -> data[i][0] = ' ';
		p -> data[i][p -> largura - 1] = ' ';
	}
	for (i = 0; i < p -> largura; i++)
	{
		p -> data[0][i] = ' ';
		p -> data[p -> altura - 1][i] = ' ';
	}
	for (i = 1; i < p -> altura-1; i++)
	{
		for (k = 1; k < p -> largura-1; k++)
		{
			p -> data[i][k] = ' ';
		}
	}

	int cont = 0;
	for (i = 3; i < p -> largura - 3; i+= 7)
	{
		gera_alien(l,p,1,i,1,++cont);
		p -> numero_aliens++;
	}
	int cont2 = 0;
	for (i = 3; i < p -> largura - 5 ; i+= 7)
	{
		int cont = 1;
		gera_alien(l,p,6,i,2,++cont2);
		p -> numero_aliens++;
	}

	int cont3 = 0;
	for (i = 3; i < p -> largura - 5 ; i+= 7)
	{
		int cont = 1;
		gera_alien(l,p,12,i,3,++cont3);
		p -> numero_aliens++;
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
void surge_nave(t_lista *l, mapa *m)
{
	int i,k;
	t_nodo *aux;
	aux = l -> end;
	for (i = 0 ; i < aux -> alt; i++)
	{
		for (k = 0 ; k <  aux -> larg ; k++)
		{
			m -> data[aux -> lin + i][aux -> col + k] = aux -> data[i][k];
		}
	}

	m -> data[aux -> lin + 1][aux -> col - 1 ] = ' ';
}
void inicia_nave(t_lista *l)
{
	t_nodo *aux;
	aux = l -> end;
	aux -> lin = 2;
	aux -> col = 2;
	aux -> data = malloc(3*sizeof(aux -> data));
	for (int i = 0; i < 3; i++)
	{
		aux -> data[i] = malloc(9*sizeof(aux -> data));
	}
	aux -> data[0][0] = ' ';
	aux -> data[0][1] = '/';
	aux -> data[0][2] = 'M';
	aux -> data[0][3] = 'M';
	aux -> data[0][4] = 'M';
	aux -> data[0][5] = 'M';
	aux -> data[0][6] = 'M';
	aux -> data[0][7] = '\\';
	aux -> data[0][8] = ' ';
	aux -> data[1][0] = 'A';
	aux -> data[1][1] = 'M';
	aux -> data[1][2] = '0';
	aux -> data[1][3] = 'M';
	aux -> data[1][4] = '0';
	aux -> data[1][5] = 'M';
	aux -> data[1][6] = '0';
	aux -> data[1][7] = 'M';
	aux -> data[1][8] = 'A';
	aux -> data[2][0] = ' ';
	aux -> data[2][1] = '\\';
	aux -> data[2][2] = '/';
	aux -> data[2][3] = '\'';
	aux -> data[2][4] = '-';
	aux -> data[2][5] = '\'';
	aux -> data[2][6] = '\\';
	aux -> data[2][7] = '/';
	aux -> data[2][8] = ' ';
	
}
void inicia_barreira(t_lista *l)
{
	t_nodo *aux;
	aux = l -> end;
	aux -> data = malloc(3*sizeof(aux -> data));
	for (int i = 0; i < 3; i++)
	{
		aux -> data[i] = malloc(7*sizeof(aux -> data));
	}
	aux -> data[0][0] = 'A';
	aux -> data[0][1] = 'M';
	aux -> data[0][2] = 'M';
	aux -> data[0][3] = 'M';
	aux -> data[0][4] = 'M';
	aux -> data[0][5] = 'M';
	aux -> data[0][6] = 'A';
	aux -> data[1][0] = 'M';
	aux -> data[1][1] = 'M';
	aux -> data[1][2] = 'M';
	aux -> data[1][3] = 'M';
	aux -> data[1][4] = 'M';
	aux -> data[1][5] = 'M';
	aux -> data[1][6] = 'M';
	aux -> data[2][0] = 'M';
	aux -> data[2][1] = 'M';
	aux -> data[2][2] = 'M';
	aux -> data[2][3] = 'M';
	aux -> data[2][4] = 'M';
	aux -> data[2][5] = 'M';
	aux -> data[2][6] = 'M';
}
void imprime_barreiras(mapa *m,t_nodo *n)
{
	int i,k;
	for (i = 0; i < n -> alt; i++)
	{	
		for (k = 0; k < n -> larg; k++)
		{
			m -> data[n -> lin + i][n -> col + k] = n -> data[i][k];
		}
	}	
}

void alien_atira(t_lista *l , placa_a *p, int number)
{
	
	t_nodo *aux;
	t_nodo *chose;
	chose = NULL;
	aux = l -> begin;
	int tam = 0;
	srand(time(NULL));
	int r = (rand() % (number))+1;
	while(aux != NULL)
	{
		if ((aux -> type >= 2) && (aux -> type <= 4))
		{
			if (aux -> unity == r)
			{
				chose = aux;
			}
		}
		aux = aux -> next;			
	}
	if (chose != NULL)
	{
		//printf("%d %d\n",chose -> lin, chose -> unity );
		if (chose -> type == 2)
				p -> data[chose -> lin + chose -> alt][chose -> col + chose -> larg/2] = '@';
		else
				p -> data[chose -> lin + chose -> alt - 2][chose -> col + chose -> larg/2] = '@';
	}
	/* TEM QUE ARRUMAR O NUMERO DE ALIENS NO NUMBER, OU SEJA ACERTAR O MESMO NUMERO POR LINHAS */
	
}

void busca_tiro_sai(placa_a *p, mapa *m)
{
	int i;
	for (i = 0; i < p -> largura; i++)
	{
		if (p -> data[p -> altura - 1][i] == '@')
		{
			p -> data[p -> altura - 1 ][i] = ' ';
			m -> data[p -> linha + p -> altura][p -> coluna + i] = '@'; 
		}

	}
}
void gera_alien(t_lista *l,placa_a *p, int linIni,int colIni, int tipo, int n)
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
		insere_fim_lista(tipo + 1,linIni,colIni,3,3,1,n,l);
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
		insere_fim_lista(tipo + 1,linIni,colIni,5,5,1,n,l);
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
		insere_fim_lista(tipo + 1,linIni,colIni,5,5,1,n,l);
	}
}

int chocou(placa_a *p, t_lista *l, mapa *m)
{
	if (p -> linha + p -> altura == m -> linhas - 9)
	{
		remove_barreira(l,m);
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
void tiros(t_lista *l,placa_a *p, mapa *m, int right, int *changed, int *score, int *mae)
{
	atinge_alien(l, p, score);
		
	entra_tiro(m,p);

	busca_tiro(m);

	sai_tiro(m, p);

	busca_tiro_alien(m, right);

	busca_tiro_placa(p, right, changed);

	busca_tiro_sai(p, m);

	atinge_mae(l, m, score, mae);

	//busca_tiro_alien_placa(p, right, changed);

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
	m -> data[n -> lin -1][n -> col+2] = 'o';
}
void busca_tiro(mapa *m)
{
	int i,k;
	for (i = 2; i <  m -> linhas - 2; i++)
	{
		for (k = 2; k < m -> colunas - 2; k++)
		{
			if (m -> data[i][k] == 'o')
			{
				m -> data[i-1][k] = 'o';
				m -> data[i][k] = ' ';
			}

		}
	}
}
void busca_tiro_alien(mapa *m, int right)
{
	int i,k;
	for (i =  m -> linhas - 1 ; i > 5 ; i--)
	{
		for (k = m -> colunas; k > 2; k--)
		{
			if (m -> data[i][k] ==  '@')
			{
				m -> data[i-1][k] = ' ';
				m -> data[i][k] = ' ';
				if (i < m -> linhas - 3)
				{
					if (right)
						m -> data[i+1][k + 1] = '@';
					else
						m -> data[i+1][k - 1] = '@';
				}
				
			}

		}
	}
}
void entra_tiro(mapa *m, placa_a *p)
{
	int i,k;
	for (i = 0; i < p -> largura; i++)
	{
		if (m -> data[p -> linha + p -> altura][p -> coluna + i] == 'o')
			p -> data[p->altura-1][i] = 'o';
	}
	for (k = 0 ; k < p -> altura; k++)
	{
		if (m -> data[p -> linha + k][p -> coluna - 1] == 'o')
		{
			p -> data[k][0] = 'o';
			m -> data[p -> linha + k][p -> coluna - 1] = ' ';
		}
	}
	for (k = 0 ; k < p -> altura; k++)
	{
		if (m -> data[p -> linha + k][p -> coluna + p -> largura] == 'o')
		{
			p -> data[k][p -> largura - 1 ] = 'o';
			m -> data[p -> linha + k][p -> coluna + p -> largura] = ' ';
		}
	}
}
void sai_tiro(mapa *m, placa_a *p)
{
	int i;
	for (i = 0; i < p -> largura; i++)
	{
		if (p -> data[0][i] == 'o')
		{
			m -> data[p -> linha - 1][p -> coluna + i ] = 'o';
			p -> data[0][i] = ' ';
		}

	}
}
void busca_tiro_placa(placa_a *p, int dir, int *changed)
{
	int i,k;
	for (i = 0; i <  p -> altura ; i++)
	{
		for (k = 0; k < p ->  largura; k++)
		{
			if (p -> data[i][k] == 'o')
			{
				if (*changed == 0)
				{
					if (dir)
						p -> data[i-1][k-1] = 'o';
					else
						p -> data[i-1][k+1] = 'o';
					p -> data[i][k] = ' ';

				}	
				else
				{
					if (dir)
						p -> data[i-1][k+1] = 'o';
					else
						p -> data[i-1][k-1] = 'o';
					p -> data[i][k] = ' ';
					*changed = 0;
				}
				
			}
		
		}
	}
	int j, f;
	j = 0;
	f = 0;
	

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
void atinge_alien(t_lista *l, placa_a *p, int *score)
{
	int i,k;
	t_nodo *n;
	n = l -> begin;
	while (n != NULL)
	{
		if (n -> type >= 2 && n -> type <= 4)
		{
			for (i = n -> lin ; i < n -> lin + n -> alt; i++)
			{
				for (k = n -> col; k < n -> col + n -> larg; k++)
				{
					if (p -> data[i][k] == 'o')
					{
						n -> state = 0;
						busca_e_remove(l,p);
						if (n -> type == 2)
						{
							*score+=25;
						}
						else if (n -> type == 3)
						{
							*score+=15;
						}
						else
						{
							*score+=5;
						}

					}
				}
			}
		}
		n = n -> next;
	} 
}
void atinge_mae(t_lista *l, mapa *m, int *score, int *mae)
{
	if (*mae)
	{
		int i,k;
		int j,p;
		t_nodo *n;
		n = l -> end;
		for (i = n -> col ; i < (n -> col + n -> larg - 1) ; i++)
		{
				if (m -> data[n -> lin + n -> alt - 1 ][i] == 'o')
				{
					
					for (j = n -> lin ; j < n -> lin + n -> alt; j++)
					{
						for (p = n -> col; p < n -> col + n -> larg ; p++)
						{
							m -> data[j][p] = ' ';

						}
					}
					n -> col = 2;
					*mae = 0;


					*score += 200;
					printf("hitou\n");
				}
		}
	}
}

void busca_e_remove(t_lista *l, placa_a *p)
{
	t_nodo *n;
	t_nodo *aux;
	int i,k;
	int val = 0;
	n = l -> begin;
	while (n != NULL)
	{
		if (n -> type >= 2 && n -> type <= 4)
		{
			if (n -> state == 0)
			{
				for (i = n -> lin ; i < n -> lin + n -> alt ; i++)
				{
					for (k = n -> col; k < n -> col + n -> larg ; k++)
					{
						p -> data[i][k] = ' ';
					}
				}
				val = 1;
				aux = n -> next;
				remove_nodo(l,n);
				n = aux;
				p -> numero_aliens--;
			}
			
		}
		if (!val)
			n = n -> next;
		else
			val = 0;
	}
}

void remove_barreira(t_lista *l, mapa *m)
{
	t_nodo *n;
	t_nodo *aux;
	int i,k;
	int val = 0;
	n = l -> begin;
	while (n != NULL)
	{
		if (n -> type == 5)
		{
				for (i = n -> lin ; i < n -> lin + n -> alt ; i++)
				{
					for (k = n -> col; k < n -> col + n -> larg ; k++)
					{
						m -> data[i][k] = ' ';
					}
				}
				val = 1;
				aux = n -> next;
				remove_nodo(l,n);
				n = aux;
		}
		if (!val)
			n = n -> next;
		else
			val = 0;
	}
}
int atinge_canhao(t_lista *l, placa_a *p , mapa *m)
{
	
	if ((p -> linha +  p -> altura - 1) == m -> linhas - 4 )
		return 1;
	return 0;
}
void limpa_topo(mapa *m)
{
	int i;
	for (i = 1; i < m -> colunas; i++)
	{
		m -> data[1][i] = ' ';
	}
}