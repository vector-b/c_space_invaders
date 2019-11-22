#include <stdio.h>
#include <stdlib.h>
#include "space.h"
int enfileira(int lin, int col, t_fila *f)
{
        tiro *y;
        tiro *novo;
        novo = malloc(40*sizeof(novo));
        if (!novo)
        {
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
        }
        f -> size++;
}