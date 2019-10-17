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
	int linhas;
	int colunas;
	int numero_aliens;

}placa_alienigiena;

mapa *geramapa(mapa *m, int nlin, int ncol);
alien *inicializa_placa(mapa *m, placa *p, int linIni, int colIni)
{
	
}





#endif