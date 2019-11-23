#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "space.h"
int main()
{
	/* Declaração de variaveis auxiliares */ 
	int lin,col;
	int tlin,tcol;
	int score, right, changed, canhao_atingido, contador, limitador, ganhou, co,  i, j;
	
	/*Inicialização das variaveis */
	score = 0;
	ganhou = 1;
	last = 0;
	canhao_atingido = 0;
	co = 0;
	contador = 1;
	limitador = 21;

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

    /* Tamanho da tela */
	lin = 37;
	col = 150;

	/* Verificação -> tamanho da tela */
	if (tlin < 37 || tcol < 150)
	{
		endwin();
		printf("Tamanho de tela insuficiente\n");
		exit(1);
	}

	/* Inicia o mapa */
	mapa *m;
	m = malloc(sizeof(m));
	/* Inicia a placa que move os aliens */
	placa_a *placa;
	placa = malloc(sizeof(placa));
	/* Inicia a lista de objetos do programa */ 
	t_lista *obj;
	/* Inicia a fila de tiros do aliens */
	t_fila *tiros_alien;


	/* Inicia a dificuldade  6 -> 1 */  
	int dificuldade = 6;

while(dificuldade > 0)
{
	co = 0;
	/* Realoca as listas a cada nova fase */
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


	while (ganhou) /*Enquanto ainda não perdeu, prossiga*/
	{

		int seed = 0;

		/* Diminui o tamanho da placa quando uma fileira de aliens morre */
		diminui_placa(obj,placa);

		/* Imprime os tiros de aliens na tela */
		imprime_tiro(tiros_alien);

		/* Atualiza a posição do tiro dos aliens na fila*/
		atualiza_tiro(tiros_alien, obj, &canhao_atingido,m);

		/* Se canhão for atingido = Game Over */
		if (canhao_atingido)
		{
			ganhou = 0;
		}
		/* Se os aliens acabarem = Proximo level ou vitoria */
		if (placa -> numero_aliens == 0)
			break;

		/* Se a placa atingir o canhao = perdeu */
		if (atinge_canhao(obj, placa, m))
			ganhou = 0;
		
		limpa_topo(m);
		
		/* Se a nave_mae esta ativa, caminha para a direita */
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
		/* Caso o contador seja um multiplo de 120, a nave mãe irá aparecer */
		if (contador % 120  == 0)
		{
			surge_nave(obj,m);
			mae = 1;
		}


		/* mod  server para verificar se os aliens estão se mexendo, mod = 0 nivel mais rapido */ 
		int mod = temporizador % dificuldade;

		/*Função que contém outras funções para direcionar e guiar os tiros pelo jogo*/
		tiros(obj,placa, m, right, &changed, &score, &mae, mod);

		/*Função que determina se os aliens chegaram até o canhão */
		chocou(placa,obj,m);
		
		refresh();

		/* Tempo usado por default no andamento do jogo, principalmente na movimentação do canhão */
		usleep(50000);

		clear();

		/* Semelhante a nave mãe, essa função regula os tiros dos aliens pra mod (21 - 3i), sendo i o numero da fase*/
		if (co % limitador == 0)
		{
			srand(time(NULL));
			int r = rand() % 2;

			if (r == 1)
			{
				seed++;
				if (seed == 4)
				seed = 0;
				tiros_alien = alien_atira(obj, placa, number,tiros_alien, &seed);
			}
		}
		

		/* Regula o andamento da placa de aliens, e assim determina sua velocidade */
		if (temporizador % dificuldade == 0)
		{
			/* Responsavel pela colisão com as laterais do mapa */
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

			/* Se está indo pra direita, aumenta coluna, senão diminui, assim a placa de aliens se move*/
			if (right)
				placa -> coluna++;
			else
				placa -> coluna--;

			/* Deleta as colunas printadas na posição anterior */
			if (right)
				deletecolumn(m,placa,&right);
			else
				deletecolumn(m,placa,&right);


		}

		/* Atualiza a  placa no mapa */
		transicao(m,placa);

		
		/* Utilizado para chegar as teclas pressionadas pelo usuario, assim movimentando e atirando o canhão */ 
		/*  <-   a*/
		/*  ->   d*/
		/*  p   shoot*/
		/*  ESC SAIR */
		switch(getch()) 
		{
    		case 'd':
    		{
    			if (obj -> begin -> col + obj -> begin -> larg -1  != 146)
    			{
    				obj -> begin -> col++;
    			}	
        		break;
    		}
    		case 'a':
    		{
    			if (obj -> begin -> col != 2)
    			{
    				obj -> begin -> col--;

    			}
        		break;
    		}
    		case 'p':
    		{
    			atirar(obj -> begin,m);
        		break;
    		}
    		case 'l':
    		{
    			ganhou = 0;
        		break;
    		}

		}	

		imprime_canhao(obj -> begin ,m);

		move(1,70);
		/* Pontuacao, exibida acima do mapa */
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
		co++;

	}
	limitador -= 3;
	dificuldade--;
	free(obj);
	if (!ganhou)
		break;
	else
	{
		if (dificuldade != 0)
		{
			/* Next Level */ 
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
		sleep(4);
	}
}



	/* Desaloca o que for necessário */
	free(m);
	free(obj);
	free(placa);
	free(obj);
	free(m);
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
