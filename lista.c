#include <stdio.h>
#include <stdlib.h>
#include "space.h"

/*Criação da lista*/
int cria_lista(t_lista *l)
{
	l -> size = 0;
	l -> begin = NULL;
	if (l -> begin == NULL)
		return 1;
	return 0;
}
/*Checa se a lista se encontra vazia*/
int lista_vazia(t_lista *l)
{
	if ((l -> size == 0) || ((l -> begin) == NULL)) 
		return 1;
	else
		return 0;
	return 0;
}

/*Insere no começo da lista, pelo ini*/
int insere_fim_lista(int type, int lin, int col, int al, int la, int state, int unity, t_lista *l)
{
	t_nodo *n;
	t_nodo *aux;
	n = malloc(86*sizeof(n));
	n -> type = type;
	n -> lin = lin;
	n -> col = col;
	n -> alt = al;
	n -> larg = la;
	n -> state = state;
	n -> unity = unity;
	if ( l -> begin == NULL)
	{
	     n -> next = NULL;
	     n -> prev = NULL;
	     l -> begin = n;
	     l -> end = n;
	}
	else
	{
		aux = l -> end;
		aux -> next = n;
		n -> prev = aux;
		n -> next = NULL;
		l -> end = n;
	}
	l -> size++;
	return 1;
}
void imprime_lista(t_lista *l)
{
 	t_nodo *aux;
 	aux = l -> begin;
 	while(aux != NULL)
 	{
 		printf("%d %d %d %d %d %d \n",aux -> type, aux -> lin, aux -> col, aux -> alt, aux -> larg, aux -> state);
 		aux = aux -> next;
 	}
}

int remove_nodo(t_lista *l, t_nodo *n)
{
	if (n -> next != NULL)
	{
		n -> prev -> next = n -> next;
		n -> next -> prev = n -> prev;
		/*free(n);*/	
	}
	else
	{
		n -> prev -> next = NULL;
	}
	l -> size--;
	return 1 ;
}
