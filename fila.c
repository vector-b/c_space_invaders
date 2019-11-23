#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "space.h"
int enfileira(int lin, int col, t_fila *f)
{
        tiro *y;
        tiro *novo;
        novo = malloc(40*sizeof(novo));
        if (!novo)
          return 0;

           if (f -> end == NULL)
           {
                f -> begin = novo;
                f -> end = novo;
           }
           else
           {
                y = f -> end;
                y -> next = novo;
                f -> end = novo;
           }
           novo -> next = NULL;
           novo -> lin = lin;
           novo -> col = col;

        f -> size++;
}
void imprime_fila(t_fila *f)
{
    tiro *aux;
    aux = f -> begin;
    while(aux != NULL)
    {
      printw("%d %d\n",aux ->lin, aux -> col);
      aux = aux -> next;
    }
}