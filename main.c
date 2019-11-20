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


	/* Inicialização dos recursos ncurses */
	initscr();				
	clear();	
	refresh();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
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
	m = inicia_mapa(m,lin,col);


	t_lista *obj;
	obj  = malloc(sizeof(obj));
	
	/* Inicia o canhão */
	insere_fim_lista(1, (lin - 4), (col/2)-4, 2, 5, 1, 1, obj);
	inicia_canhao(obj,m);

	/*for (int i = 0; i < 6; i++)
	{
		insere_fim_lista(2+i,2,12,3,3,1,obj);
		insere_fim_lista(9+i,2,12,3,3,1,obj);
		insere_fim_lista(92+i,2,12,3,3,1,obj);
	}*/
	int mae = 0;

	placa_a *placa;
	placa = malloc(sizeof(placa));
	placa = inicia_placa(obj,placa, lin, col);

	int pos = 20;
	/* Inicia barreiras */
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


	//imprime_lista(obj);

	//==sleep(2);
	while (ganhou) /*ganhou, perdeu ou apertou esc*/
	{

		/*srand(time(NULL));
		int r = rand() % 2;
		if (r == 1)
		{
			alien_atira(obj, placa);
		}
		*/
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
		
		if (mae)
		{
			t_nodo *aux;
			aux = obj -> end;
			aux -> col++;
		}
		if (contador % 120  == 0)
		{
			surge_nave(obj,m);
			mae = 1;
		}

		tiros(obj,placa, m, right, &changed, &score, &mae);

		chocou(placa,obj,m);
		
		refresh();

		usleep(60000);

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
	}


	/* Desaloca o que for necessário */
	free(m);
	free(obj);
	free(placa);
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
		printw(";   | ;  __ |  :  ' ;.   : |   | /  | |  ||:   |  ;/|        |   :  | ; | '\\  ;  \\' |:   |  ;/||   |  \\ :         \n");
		printw("|   : |.' .'|  |  ;/  \\   \'   | :  | :  |,|   :   .'        .   |  ' ' ' : \\   \\  \\: ||   :   .'|   : .  /         \n");
		printw(".   | '_.' :'  :  | \\  \\ ,';   . |  ; |--' |   |  |-,        '   ;  \\; /  |  ;   \\  ' .|   |  |-,;   | |  \\         \n");
		printw("'   ; : \\  ||  |  '  '--'  |   : |  | ,    '   :  ;/|         \\   \\  ',  /    \\   \\   ''   :  ;/||   | ;\\  \\        \n");
		printw("'   | '/  .'|  :  :        |   : '  |/     |   |    \\          ;   :    /      \\   `  ;|   |    \\:   ' | \\.'        \n");
		printw("|   :    /  |  | ,'        ;   | |`-'      |   :   .'           \\   \\ .'        :   \\ ||   :   .':   : :-'          \n");
		printw(" \\   \\ .'   `--''          |   ;/          |   | ,'              `---`           '---\" |   | ,'  |   |.'            \n");
		printw("  `---`                    '---'           `----'                                      `----'    `---'              \n");
	}
	else
	{
		printw(" _____  ___    _______  ___  ___  ___________      ___       _______  ___      ___  _______  ___     \n");
		printw("(\\\"   \\|\"  \\  /\"     \"||\"  \\/\"  |(\"     _   \")    |\"  |     /\"     \"||\"  \\   /\"  |/\"     \"||\"  |  \n");
		printw("|.\\     \\   |(: ______) \\  \\  /  )__/  \\__/     ||  |    (: ______) \\  \\ //  /(: ______)||  |    \n");
		printw("|: \\     \\  | \\/    |    \\  \\/      \\_ /        |:  |     \\/    |    \\  \\/. ./  \\/    |  |:  |     \n");
		printw("|.  \\    \\. | // ___)_   /\\.  \\      |.  |         \\  |___  // ___)_    \\.    //   // ___)_  \\  |___  \n");
		printw("|    \\    \\ |(:      \"| /  \\  \\     \\:  |        ( \\_|:  \\(:      \"|    \\   /   (:      \"|( \\_|:  \\  \n");
		printw(" \\___|\\____\\) \\_______)|___/\\___|     \\__|         \\_______)\\_______)     \\__/     \\_______) \\_______)\n");

		/* Finaliza as alterações do ncurses */
	}
	refresh();
	sleep(6);
	getch();
 	endwin();
	return 0;
}
