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
        return 1;
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
int desenfileira(t_fila *f)
{
   tiro *aux;
   if (f -> begin == NULL && f -> end == NULL)
   {
       return 1;
   }
   else if ( f -> begin  !=  f -> end )
   {
       aux = f -> begin;
       f -> begin = f -> begin -> next;
       free(aux);
   }
   else
   {
       aux = f -> begin;
       f -> begin = NULL;
       f -> end  = NULL;
       free(aux);
   }
   return 1;
}