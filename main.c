#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "space.h"
int main()
{
	int lin,col;
	int tlin,tcol;
	int score = 0;
	int i,j,right,changed;
	int ganhou = 1;
	int last = 0;
	int canhao_atingido = 0;


	//system("mpg123 lavender.mp3 &");
	/* Inicialização dos recursos ncurses */
	initscr();				
	clear();	
	refresh();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	wattron(stdscr, COLOR_PAIR(1));
	getmaxyx(stdscr, tlin, tcol);
	cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */
	lin = 37;
	col = 150;


	if (tlin < 37 || tcol < 150)
	{
		endwin();
		printf("Tamanho de tela insuficiente\n");
		exit(1);
	}
	int contador = 1;
	/* Inicia o mapa */
	mapa *m;
	m = malloc(sizeof(m));

	placa_a *placa;
	placa = malloc(sizeof(placa));

	t_lista *obj;


	t_fila *tiros_alien;


	int dificuldade = 6;

while(dificuldade > 0)
{

	obj  = malloc(sizeof(obj));

	obj -> begin = NULL;


	tiros_alien = malloc(sizeof(tiros));

	tiros_alien -> size = 0;






	int temporizador = 1;
	
	/* Inicia o canhão */
	m = inicia_mapa(m,lin,col);
	insere_fim_lista(1, (lin - 4), (col/2)-4, 2, 5, 1, 1, obj);
	inicia_canhao(obj,m);
	placa = inicia_placa(obj,placa, lin, col);
	int mae = 0;



	int pos = 20;
	/* Inicia barreiras */
	/* Barreira -> tipo 5 // 4 Unidades */
	insere_fim_lista(5, lin-9, pos, 3, 7, 1, 1, obj);
	inicia_barreira(obj);
	imprime_barreiras(m,obj -> end);

	insere_fim_lista(5, lin-9, pos+=35, 3, 7, 1, 2, obj);
	inicia_barreira(obj);
	imprime_barreiras(m,obj -> end);

	insere_fim_lista(5, lin-9, pos+=35, 3, 7, 1, 3, obj);
	inicia_barreira(obj);
	imprime_barreiras(m,obj -> end);

	insere_fim_lista(5, lin-9, pos+=35, 3, 7, 1, 4, obj);
	inicia_barreira(obj);
	imprime_barreiras(m,obj -> end);
	
	/* Inicia Nave Mãe */
	insere_fim_lista(6, 0, 0, 3, 9, 1, 1, obj);
	inicia_nave(obj);

	/*Número de aliens por linha */
	int number = placa -> numero_aliens / 3;


	while (ganhou) /*ganhou, perdeu ou apertou esc*/
	{


		diminui_placa(obj,placa);

		srand(time(NULL));
		int r = rand() % 2;

		if (r == 1)
		{
			tiros_alien = alien_atira(obj, placa, number,tiros_alien);
		}

		imprime_tiro(tiros_alien);

		atualiza_tiro(tiros_alien, obj, &canhao_atingido);

		if (canhao_atingido)
		{
			ganhou = 0;
		}
		if (placa -> numero_aliens == 0)
			break;

		if (atinge_canhao(obj, placa, m))
			ganhou = 0;
		
		limpa_topo(m);
		
		if (mae)
		{
			t_nodo *aux;
			aux = obj -> end;
			aux -> col++;
			if (aux -> col == 150)
			{
				aux -> col = 2;
				mae = 0;
				contador++;
			}


		}
		if (contador % 120  == 0)
		{
			surge_nave(obj,m);
			mae = 1;
		}

		int mod = temporizador % dificuldade;

		tiros(obj,placa, m, right, &changed, &score, &mae, mod);

		chocou(placa,obj,m);
		
		refresh();

		usleep(50000);

		clear();

		/* Empurra a placa pro lado */

		if (temporizador % dificuldade == 0)
		{


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

			if (right)
				placa -> coluna++;
			else
				placa -> coluna--;

			if (right)
				deletecolumn(m,placa,&right);
			else
				deletecolumn(m,placa,&right);

		}

		/* Atualiz a placa no mapa */
		transicao(m,placa);

		/* Apaga a parte da placa que ficou pra tras */ 
	
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

		move(1,70);
		printw("SCORE: %d\n",score );
		/* Printa o mapa e tudo o que estiver dentro */
		for (i = 0; i < (m -> linhas); i++)
		{
			for (j = 0; j < (m -> colunas); j++)
				printw("%c", m -> data[i][j]);
			printw("\n");
		}
		if (!mae)
			contador++;

		temporizador++;



	}
	dificuldade--;
	free(obj);
	if (!ganhou)
		break;
	else
	{
		if (dificuldade != 0)
		{
			clear();
			printw("/\\ \"-.\\ \\   /\\  ___\\   /\\_\\_\\_\\   /\\__  _\\    /\\ \\       /\\  ___\\   /\\ \\ / /  /\\  ___\\   /\\ \\       \n");
			printw("\\ \\ \\-.  \\  \\ \\  __\\   \\/_/\\_\\/_  \\/_/\\ \\/    \\ \\ \\____  \\ \\  __\\   \\ \\ \' /   \\ \\  __\\   \\ \\ \\____  \n");
			printw(" \\  \\_\\\"\\_\\  \\ \\_____\\   /\\_\\/\\_\\    \\ \\_\\     \\ \\_____\\  \\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_____\n");
			printw("  \\/_/ \\/_/   \\/_____/   \\/_/\\/_/     \\/_/      \\/_____/   \\/_____/   \\/_/      \\/_____/   \\/_____/ \n");
			refresh();
			sleep(4);
		}
		

	}
	
	if (dificuldade == 0)
	{
		clear();
		printw("  __  __     ______     __  __        __     __     __     __   __       \n");
		printw(" /\\ \\_\\ \\   /\\  __ \\   /\\ \\/\\ \\      /\\ \\  _ \\ \\   /\\ \\   /\\ \"-.\\ \\     \n ");
		printw("\\ \\___\\ \\  \\ \\/\\ \\ \\  \\   \\_\\ \\     \\ \\ \\/ \".\\ \\  \\ \\ \\  \\ \\ \\-.  \\     \n");
		printw("  \\/\\_____\\  \\ \\_____\\  \\ \\_____\\     \\ \\__/\".~\\_\\  \\ \\_\\  \\ \\_\\ \"\\_\\   \n ");	
		printw("  \\/_____/   \\/_____/   \\/_____/      \\/_/   \\/_/   \\/_/   \\/_/ \\/_/ \n");
		refresh();
		sleep(8);
	}
}

	



	//imprime_lista(obj);

	//==sleep(2);


	/* Desaloca o que for necessário */
	free(m);
	free(obj);
	free(placa);
	free(obj);
	/*for (int i = 0; i < lin; i++)
	{
		free(m -> data[i]);
	}
	free(m -> data);
	free(m);*/
	/*Desalocar placa*/
	/*Desalocar mapa*/

	clear();
	if (!ganhou)
	{
    	printw("                                     ____                        ,----..                                            \n");
		printw("  ,----..      ,---,               ,'  , `.    ,---,.           /   /   \\                  ,---,.,-.----.           \n");
		printw(" /   /   \\    '  .' \\           ,-+-,.' _ |  ,'  .' |          /   .     :        ,---.  ,'  .' |\\    /  \\          \n");
		printw("|   :     :  /  ;    '.      ,-+-. ;   , ||,---.'   |         .   /   ;.  \\      /__./|,---.'   |;   :    \\         \n");
		printw(".   |  ;. / :  :       \\    ,--.'|'   |  ;||   |   .'        .   ;   /  ` ; ,---.;  ; ||   |   .'|   | .\\ :\n");
		printw(".   ; /--`  :  |   /\\   \\  |   |  ,', |  '::   :  |-,        ;   |  ; \\ ; |/___/ \\  | |:   :  |-,.   : |: |         \n");
		printw(";   | ;  __ |  :  ' ;.   : |   | /  | |  ||:   |  ;/|        |   :  | ; | '\\  ;  \\' |:  |  ;/||   |  \\ :         \n");
		printw("|   : |.' .'|  |  ;/  \\   \'   | :  | :  |,|   :   .'         .   |  ' ' ' : \\   \\  \\: ||   :   .'|   : .  /         \n");
		printw(".   | '_.' :'  :  | \\  \\ ,';   . |  ; |--' |   |  |-,        '   ;  \\; /  |  ;   \\  ' .|   |  |-,;   | |  \\         \n");
		printw("'   ; : \\  ||  |  '  '--'  |   : |  | ,    '   :  ;/|         \\   \\  ',  /    \\   \\   ''   :  ;/||   | ;\\  \\        \n");
		printw("'   | '/  .'|  :  :        |   : '  |/     |   |    \\          ;   :    /      \\   `  ;|   |    \\:   ' | \\.'        \n");
		printw("|   :    /  |  | ,'        ;   | |`-'      |   :   .'           \\   \\ .'        :   \\ ||   :   .':   : :-'          \n");
		printw(" \\   \\ .'   `--''          |   ;/          |   | ,'              `---`           '---\" |   | ,'  |   |.'            \n");
		printw("  `---`                    '---'           `----'                                      `----'    `---'              \n");
	}
	
	refresh();
	sleep(6);
	getch();
 	endwin();
	return 0;
}
