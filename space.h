#ifndef __SPACE__
#define __SPACE__

typedef struct nodo 
{
    /* 1-canhao 2-alien  3-alien(2) 4-alien(3) 5-barreira 6-nava mãe */
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

    /* Tamanho do objeto em largura */
    int tam;

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

int insere_fim_lista(int type, int lin, int col, int tam, int state, lista *l);


/* Funções do jogo */

mapa *geramapa(mapa *m, int nlin, int ncol);

placa_a *inicializa_placa(lista *l,mapa *m, placa_a *p, int linIni, int colIni);

void ande_alien(mapa *m, placa_a *p);

void deletecolumn(mapa *m, placa_a *p, int *right);

void deletetop(mapa *m, placa_a *p);

lista *cria_alien(lista *l, placa_a *p, int linIni,int colIni,int tipo);

lista *inicia_canhao(lista *l, mapa *m);

void imprime_canhao(nodo *n, mapa *m);

void atirar(nodo *n,mapa *m);

void busca_tiro(mapa *m);

void entra_tiro(mapa *m, placa_a *p);

void busca_tiro_placa(placa_a *p, int dir, int *changed);

void sai_tiro(mapa *m, placa_a *p);
#endif