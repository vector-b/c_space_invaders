#include <stdio.h>
#include <stdlib.h>
#include "space.h"
int inicia_lista(lista *l)
{
	if (!l)
		return 0;
	l -> begin = NULL;
	l -> go = NULL;
	l -> end = NULL;
	l -> size = 0;
	return 1;
}
int insere_inicio_lista(int type, int lin, int col, int tam, int state, lista *l)
{
	nodo *nodo;
	nodo = malloc(sizeof(nodo));
	nodo -> type = type;
	nodo -> lin = lin;
	nodo -> col = col;
	nodo -> state = state;
	nodo -> tam = tam;
	if (l -> begin == NULL)
	{
		l -> begin = nodo;
		nodo -> next = NULL;
		nodo -> prev = NULL;
		l -> end  = nodo;
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
int insere_fim_lista(int type, int lin, int col, int tam, int state, lista *l)
{
	nodo *n;
	n = malloc(sizeof(n));
	n -> type = type;
	n -> lin = lin;
	n -> col = col;
	n -> state = state;
	n -> tam = tam;
	if (l -> begin == NULL)
	{
		l -> begin = n;
		n -> next = NULL;
		n -> prev = NULL;
	}
	else
	{
		n -> next = NULL;
		n -> prev = l -> end;
		l -> end -> next = n;
		l -> end = n;
	}
	l -> size++;
	return 1;
}