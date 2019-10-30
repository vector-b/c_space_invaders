#ifndef __SPACE__
#define __SPACE__

typedef struct mapa
{   
    char **data;
    int linhas;
    int colunas;
} mapa;

typedef struct alien
{
	int vivo;
	int tipo; /* 1 -3 */
	int ini_lin, ini_col;
	int end_lin, end_col;
}alien;

typedef struct placa_alienigiena
{
	char **data;
	int linha;
	int coluna;
	int altura;
	int largura;
	int numero_aliens;

}placa_a;

mapa *geramapa(mapa *m, int nlin, int ncol);
placa_a *inicializa_placa(mapa *m, placa_a *p, int linIni, int colIni);
void ande_alien(mapa *m, placa_a *p);
void deletecolumn(mapa *m, placa_a *p, int *right);
void deletetop(mapa *m, placa_a *p);



#endif