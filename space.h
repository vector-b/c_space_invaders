struct t_nodo {
    /* 1-canhao 2-alien  3-alien(2) 4-alien(3) 5-barreira 6-nave mãe  */
    int type;
    int lin;
    int col;
    char **data;
    int vel;
    int state;
    int alt;
    int larg;
    int unity;
    struct t_nodo *next;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *begin;
    t_nodo *end;
    int size;
};
typedef struct t_lista t_lista;

typedef struct tiro
{
    struct tiro *next;
    int lin;
    int col;
}tiro;
typedef struct t_fila
{
     struct tiro *begin;
     struct tiro *end;
     int size;
}t_fila;
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

/* Funções de manipulação da Fila */

int enfileira(int lin, int col, t_fila *f);
void imprime_fila(t_fila *f);
int desenfileira(t_fila *f);


/* Funções de manipulação da lista */
int cria_lista(t_lista *l);
int lista_vazia(t_lista *l);
void destroi_lista(t_lista *l);
int insere_fim_lista(int type, int lin, int col, int al, int la, int state, int unity, t_lista *l);
void imprime_lista(t_lista *l);
int remove_nodo(t_lista *l, t_nodo *n);

/* Funções de manipulação das matrizes e objetos do jogo */
placa_a *inicia_placa(t_lista *l,placa_a *p, int lin, int col);

mapa *inicia_mapa(mapa *m, int lin, int col);

void inicia_canhao(t_lista *l, mapa *m);

void inicia_nave(t_lista *l);

void gera_alien(t_lista *l,placa_a *p, int linIni,int colIni, int tipo, int n);

void transicao(mapa *m, placa_a *p);

void deletecolumn(mapa *m, placa_a *p, int *right);

void deletetop(mapa *m, placa_a *p);

void atirar(t_nodo *n, mapa *m);

void busca_tiro(mapa *m);

void atualiza_tiro(t_fila *f, t_lista *l, int *canhao, mapa *m);

void imprime_tiro(t_fila *f);

t_fila  *alien_atira(t_lista *l , placa_a *p, int number, t_fila *f, int *seed);

int chocou(placa_a *p, t_lista *l, mapa *m);

void tiros(t_lista *l,placa_a *p, mapa *m, int right, int *changed, int *score, int *mae, int mod);

void entra_tiro(mapa *m, placa_a *p);

void busca_tiro_placa(placa_a *p, int dir, int *changed, int mod );

void sai_tiro(mapa *m, placa_a *p);

void imprime_canhao(t_nodo *n, mapa *m);

void diminui_placa(t_lista *l, placa_a *p);

void atinge_alien(t_lista *l, placa_a *p, int *score);

void atinge_mae(t_lista *l, mapa *m, int *score, int *mae);

void busca_e_remove(t_lista *l, placa_a *p);

void remove_barreira(t_lista *l, mapa *m);

void surge_nave(t_lista *l, mapa *m);

void inicia_barreira(t_lista *l);

void imprime_barreiras(mapa *m,t_nodo *n);

int atinge_canhao(t_lista *l, placa_a *p , mapa *m);

void limpa_topo(mapa *m);
