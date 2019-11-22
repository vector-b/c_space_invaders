#include <stdio.h>
#include <stdlib.h>
#include "space.h"
int enfileira(int lin, int col, t_fila *f)
{
        tiro *y;
        tiro *novo;
        novo = malloc(sizeof(novo));
        if (!novo)
        {
           if (f -> end == NULL)
           {
                f -> begin = novo;
                f -> end = novo;
           }
        }
}