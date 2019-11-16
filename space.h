struct t_nodo {
    int type;
    int lin;
    int col;
    char **data;
    int vel;
    int state;
    int alt;
    int larg;
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

int cria_lista(t_lista *l);
int lista_vazia(t_lista *l);
void destroi_lista(t_lista *l);
int insere_fim_lista(int type, int lin, int col, int al, int la, int state, t_lista *l);
void imprime_lista(t_lista *l);

placa_a *inicia_placa(t_lista *l,placa_a *p, int lin, int col);

mapa *inicia_mapa(mapa *m, int lin, int col);

void *inicia_canhao(t_lista *l, mapa *m);

void gera_alien(t_lista *l,placa_a *p, int linIni,int colIni, int tipo);

void transicao(mapa *m, placa_a *p);

void deletecolumn(mapa *m, placa_a *p, int *right);

void deletetop(mapa *m, placa_a *p);

void atirar(t_nodo *n, mapa *m);

void busca_tiro(mapa *m);

void entra_tiro(mapa *m, placa_a *p);

void busca_tiro_placa(placa_a *p, int dir, int *changed);

void sai_tiro(mapa *m, placa_a *p);

void imprime_canhao(t_nodo *n, mapa *m);

void atinge_alien(t_lista *l, placa_a *p);

void busca_e_remove(t_lista *l, placa_a *p);

/*int insere_fim_lista(int x, t_lista *l);
int insere_ordenado_lista(int x, t_lista *l);

int remove_primeiro_lista(int *item, t_lista *l);
int remove_ultimo_lista(int *item, t_lista *l);
int remove_item_lista(int chave, int *item, t_*/