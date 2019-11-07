typedef struct nodo 
{
    int type;
    /* 1-canhao 2-alien 3-nave 4-barreira */

    int lin;
    int col;
    
    int vel;

    int state;
    /* 1 - vivo 2 - morto */ 

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