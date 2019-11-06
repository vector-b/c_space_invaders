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
	int linIni, colIni;
	int linEnd, colEnd;
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

typedef struct canhao
{
	char **data;
	int linha;
	int coluna;
}canhao;

mapa *geramapa(mapa *m, int nlin, int ncol);
placa_a *inicializa_placa(mapa *m, placa_a *p, int linIni, int colIni);
void ande_alien(mapa *m, placa_a *p);
void deletecolumn(mapa *m, placa_a *p, int *right);
void deletetop(mapa *m, placa_a *p);
alien *cria_alien(alien *a, placa_a *p, int linIni,int colIni,int linEnd, int colEnd, int tipo);
canhao *inicia_canhao(canhao *c, mapa *m, int lin, int col);
void imprime_canhao(canhao *c, mapa *m);
void atirar(canhao *c,mapa *m);
void busca_tiro(mapa *m);
void entra_tiro(mapa *m, placa_a *p);
void busca_tiro_placa(placa_a *p, int dir, int *changed);
void sai_tiro(mapa *m, placa_a *p);



#endif