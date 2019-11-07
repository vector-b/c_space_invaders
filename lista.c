#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
lista *inicia_lista(lista *l)
{
	l = malloc(sizeof(l));
	l -> begin = NULL;
	l -> go = NULL;
	l -> end = NULL;
	l -> size = 0;
	return l;
}
int insere_inicio_lista(int type, int lin, int col, int tam, int state, lista *l)
{
	nodo *nodo;
	nodo = malloc(sizeof(nodo));
	nodo -> type = type;
	nodo -> type = type;
	nodo -> lin = lin;
	nodo -> col = col;
	nodo -> state = state;
	if (l -> begin == NULL)
	{
		l -> begin = nodo;
		nodo -> next = NULL;
		nodo -> prev = NULL;
	}
	else
	{
		nodo -> next = l -> begin;
		l -> begin -> prev = nodo;
		nodo -> prev = NULL;
		l -> begin = nodo;
	}
	l -> size++;
	return 1;	
}