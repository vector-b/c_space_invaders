#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "space.h"
int main()
{
	int lin,col;
	int i,j,right,changed;

	int ganhou = 1;

	/* Inicialização dos recursos ncurses */
	initscr();				
	clear();	
	refresh();
	getmaxyx(stdscr, lin, col);
	cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */



	int contador = 0;
	/* Inicia o mapa */
	mapa *m;
	m = malloc(sizeof(m));
	m = inicia_mapa(m,lin,col);


	t_lista *obj;
	obj  = malloc(sizeof(obj));
	
	/* Inicia o canhão */
	insere_fim_lista(1, (lin - 4), (col/2)-4, 2, 5, 1, obj);
	inicia_canhao(obj,m);

	/*for (int i = 0; i < 6; i++)
	{
		insere_fim_lista(2+i,2,12,3,3,1,obj);
		insere_fim_lista(9+i,2,12,3,3,1,obj);
		insere_fim_lista(92+i,2,12,3,3,1,obj);
	}*/
	

	placa_a *placa;
	placa = malloc(sizeof(placa));
	placa = inicia_placa(obj,placa, lin, col);

	/* Inicia Nave Mãe */
	insere_fim_lista(4, 0, 0, 3, 9, 1, obj);
	inicia_nave(obj);

	imprime_lista(obj);

	sleep(2);
	while (ganhou) /*ganhou, perdeu ou apertou esc*/
	{

		if (placa -> numero_aliens == 0)
			break;
		if (m -> data[(placa -> linha)+ (placa -> altura)][(placa -> coluna) + (placa -> largura)] == '|')
		{
			right = 0;
			changed = 1;
			deletetop(m,placa);
			deletecolumn(m,placa,&right);
		}
		else if (m -> data[(placa -> linha) -1 ][(placa -> coluna) - 1] == '|')
		{
			right = 1;
			changed = 1;
			deletetop(m,placa);
			deletecolumn(m,placa,&right);
		}

		if (atinge_canhao(obj, placa, m))
			ganhou = 0;
		
		limpa_topo(m);
		
		if (contador % 30  == 0)
		{
			//surge_nave();
		}
		atinge_alien(obj, placa);
		
		entra_tiro(m,placa);

		busca_tiro(m);

		sai_tiro(m, placa);

		busca_tiro_placa(placa,right, &changed);

		refresh();

		usleep(50000);

		clear();

		/* Empurra a placa pro lado */
		if (right)
			placa -> coluna++;
		else
			placa -> coluna--;

		/* Atualiz a placa no mapa */
		transicao(m,placa);

		/* Apaga a parte da placa que ficou pra tras */ 
		if (right)
			deletecolumn(m,placa,&right);
		else
			deletecolumn(m,placa,&right);

		switch(getch()) 
		{
    		case 'd':
    		{
    			obj -> begin -> col++;
        		break;
    		}
    		case 'a':
    		{
    			obj -> begin -> col--;
        		break;
    		}
    		case 'p':
    		{
    			atirar(obj -> begin,m);
        		break;
    		}

		}	

		imprime_canhao(obj -> begin ,m);


		/* Printa o mapa e tudo o que estiver dentro */
		for (i = 0; i < (m -> linhas); i++)
		{
			for (j = 0; j < (m -> colunas); j++)
				printw("%c", m -> data[i][j]);
			printw("\n");
		}
		contador++;
	}


	/* Desaloca o que for necessário */
	free(m);
	free(obj);
	free(placa);
	/*Desalocar placa*/
	/*Desalocar mapa*/

	/* Finaliza as alterações do ncurses */
	getch();
 	endwin();
	if (!ganhou)
	{
		printf("YOU LOSE MOTHERFUCKER\n");
	}
	else
		printf("GANHOU FDP\n");
	return 0;
}