#ifndef __SPACE__
#define __SPACE__

typedef struct nodo 
{
    /* 1-canhao 2-alien 3-nave 4-barreira */
    int type;
    
    /*posicao do item na tela*/
    int lin;
    int col;
    
    /* Conteúdo do nodo */
    char **data;

    /*velocidade de movimentão do item*/
    int vel;

    /* 1 - vivo  0 - morto */ 
    int state;

    /* Ponteiros de proximo e anterior do nodo */
    struct nodo *next;
    struct nodo *prev;
}nodo;

typedef struct lista 
{
    nodo *begin;
    nodo *go;
    nodo *end;
    int size;
}lista;





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

/*Funções de manipulação de lista */

int inicia_lista(lista *l);

int insere_inicio_lista(int type, int lin, int col, int tam, int state, lista *l);


/* Funções do jogo */

mapa *geramapa(mapa *m, int nlin, int ncol);

placa_a *inicializa_placa(mapa *m, placa_a *p, int linIni, int colIni);

void ande_alien(mapa *m, placa_a *p);

void deletecolumn(mapa *m, placa_a *p, int *right);

void deletetop(mapa *m, placa_a *p);

alien *cria_alien(alien *a, placa_a *p, int linIni,int colIni,int linEnd, int colEnd, int tipo);

void *inicia_canhao(lista *l, mapa *m);

void imprime_canhao(nodo *n, mapa *m);

void atirar(nodo *n,mapa *m);

void busca_tiro(mapa *m);

void entra_tiro(mapa *m, placa_a *p);

void busca_tiro_placa(placa_a *p, int dir, int *changed);

void sai_tiro(mapa *m, placa_a *p);
#endif