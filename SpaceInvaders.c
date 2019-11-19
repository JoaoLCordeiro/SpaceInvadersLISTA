#include "lib_spcinv.h"
#include "lib_bonito.h"

int main ()
{

	initscr();
	int janela_linha,janela_coluna;
	getmaxyx(stdscr , janela_linha , janela_coluna);
	if ((janela_linha >= 38)&&(janela_coluna >= 120))
	{
		clear();
		char key;
		curs_set(FALSE);
	
		imprime_menu(janela_linha,janela_coluna);
		refresh();
		key = getch();
	
		if (key == 's')
		{
			noecho();
			nodelay(stdscr, TRUE);	
			keypad(stdscr, TRUE);

			/* "função" que inicializa as estruturas*/	
			t_listaBar listaBar;
			char **vetorspritesA;
		        t_listaAlien listaAlien;
			t_mae *naveMae;
		        t_tiro **vetorTiros;
   	    	     	t_tiro **vetorTirosA;
 
 			Inicializa_Lista_Bar(&listaBar,janela_linha,janela_coluna-(janela_coluna/constDivTela));
                                                                                                                                          
        		vetorspritesA = (char **) malloc (18*sizeof(char*));
        		int i;
   			for ( i=0 ; i<18 ; i++)
        			vetorspritesA[i] = (char *) malloc (6*sizeof(char));
       			Inicializa_Sprites_Aliens (vetorspritesA);
                                                                                                                                          
        		Inicializa_Lista_Aliens (&listaAlien);
                                                                                                                                          
        		vetorTiros = (t_tiro **) malloc (3*sizeof(t_tiro *));
        		for (i=0 ; i<3 ; i++)
        		{
        			vetorTiros[i] = (t_tiro *) malloc (sizeof(t_tiro));
        			vetorTiros[i]->lin = 0;
        			vetorTiros[i]->col = 0;
        		}						
                                                                                                                                          
        		naveMae = (t_mae *) malloc (sizeof(t_mae));
        		naveMae->estado = MORTO;
        		naveMae->col = 0;					
                                                                                                                                          
        		vetorTirosA = (t_tiro **) malloc (5*sizeof(t_tiro *));
   			for (i=0 ; i<5 ; i++)
        		{
        			vetorTirosA[i] = (t_tiro *) malloc (sizeof(t_tiro));
        			vetorTirosA[i]->lin = 0;
      			  	vetorTirosA[i]->col = 0;
        		}	 
			/*fim da "função" que inicializa as estruturas*/

			WINDOW *jogo = newwin (janela_linha , janela_coluna-(janela_coluna/constDivTela) , 0 , 0);
			WINDOW *score = newwin(janela_linha , (janela_coluna/constDivTela) , 0 , janela_coluna-(janela_coluna/constDivTela));
			refresh();

			box(score,0,0);
			box(jogo,0,0);
			wrefresh(jogo);
			wrefresh(score);
	
			int linhaAliens   = 7;
			int colunaAliens  = 1;
			int linhaJogador  = janela_linha-3;
			int colunaJogador = janela_coluna/2;

			int intercalaS 	= 1;		/*intercala sprites*/
			int indo 	= 1;		/*controla ida pra esquerda ou direita*/
			int indice 	= 0;		/*indice do while*/
			int acabou 	= 0;		/*controla se o jogo deve ser fechado*/
			int fechou	= 0;
			int atirou 	= 0;		/*controla se houve tiro*/
			int contTiros 	= 0;		/*conta os tiros do jogador*/
			int contTirosA 	= 0;		/*conta os tiros dos aliens*/
			int contColDir 	= 0;		/*conta colunas de aliens mortos na direita*/
			int contColEsq 	= 0; 		/*conta colunas de aliens mortos na esquerda*/
			int contLin 	= 0;		/*conta as linhas de aliens mortos em baixo*/
			int resetar 	= 0;		/*controla os resets do jogo*/
			int perAlAtual 	= 20000;	/*periodo atual para os alien se mecher*/
			int perAlIni 	= 20000;	/*periodo inicial de cada reset para os alien se mecher*/
			int random;			/*variavel que administra a aleatoriedade*/
			int pontos	= 0;
			int pontosA	= 0;

			while ((!acabou)&&(!fechou))
			{
				imprime_score_e_arte(score,janela_coluna/6);			
		                mvwprintw(score, 8 , janela_coluna/12 - 4 , "%8d",pontos);
               			wrefresh(score);
				while ((indice <= constTemp)&&(! resetar)&&(!fechou))
				{
					key = getch();
					if (indice % perAlAtual == 0)					/*quando os aliens se movem*/
					{
						if (contTirosA < 5)
						{
							random = rand()%100;
							if (random > 90)
							{
								random = rand()%55;
								Alien_Atira(jogo,&contTirosA,random,linhaAliens,colunaAliens,vetorTirosA,&listaAlien);
							}
						}
						Administra_Impressao_Aliens (jogo,&colunaAliens,&linhaAliens,janela_coluna,janela_linha,vetorspritesA,&intercalaS,&listaAlien,&indo,contColEsq,contColDir,&perAlAtual);
						if (! naveMae->estado)
						{
							random = rand()%1000;
							if (random > 995)
							{
								naveMae->estado = 1;
								naveMae->col = 0;
							}
						}
					}
					if ((indice % perAlAtual/2 == 0)&&(naveMae->estado))
					{
						if (naveMae->col + 9 < janela_coluna-(janela_coluna/constDivTela))
						{
							naveMae->col++;
							Imprime_Mae(naveMae,&intercalaS,jogo);
						}
						else
						naveMae->estado = 0;
					}
	
		       	        	Move_Jogador(&atirou , contTiros , &colunaJogador , key , janela_coluna , &fechou);
					Imprime_Jogador(linhaJogador , colunaJogador , jogo);
					if (key == 'p')						
					{
						imprime_pausa (jogo,janela_linha,janela_coluna);
						nodelay(stdscr, FALSE);
						key = getch();
						while (key != 'p')
						key = getch();
						wclear(jogo);
						nodelay(stdscr, TRUE);
					}
			
					if (atirou)
					{
						Atira(linhaJogador , colunaJogador , &contTiros , vetorTiros);
						atirou = 0;
					}
					if (pontosA != pontos)
					{
						imprime_score_e_arte(score,janela_coluna/6);			
						mvwprintw(score, 8 , janela_coluna/12 - 4 , "%8d",pontos);
						wrefresh(score);
					}

					if (linhaAliens + 18 - 4*contLin >= janela_linha - 10)
					{
						if (linhaAliens + 18 - 4*contLin < janela_linha - 6)
							Destroi_Linha_Bar(&listaBar, (linhaAliens+18) - (janela_linha-10) - 4*contLin);
						else
							acabou = 1;
					}
			
					Imprime_Barreiras (&listaBar,jogo);
					Imprime_Tiros(vetorTiros,jogo);
					Imprime_TirosA(vetorTirosA,jogo);
		
					pontosA = pontos;	
					if (indice % 12000 == 0)
					{
						Administra_Tiros (&contTiros,&contTirosA,vetorTiros,vetorTirosA,&listaAlien,naveMae,&acabou,colunaAliens,linhaAliens,colunaJogador,linhaJogador,janela_linha,&listaBar,&pontos);
						Verifica_Linha_Aliens(&listaAlien,&contLin);
					}
			
					Verifica_Colunas(&contColDir,&contColEsq,&listaAlien);
	
					box(jogo,0,0);
					wrefresh(jogo);
					indice++;
					if (contColEsq + contColDir >= 11)
						resetar = 1;
					if ((indice == constTemp)&&(! acabou))
						indice  = 0;
				} /*aqui acaba o while de cada rodada*/
				naveMae->estado = MORTO;
				naveMae->col    = 0;
				perAlIni 	= perAlIni / 1.5;
				perAlAtual 	= perAlIni;
				linhaAliens 	= 5;
				colunaAliens 	= 1;
				contLin		= 0;
				contColDir 	= 0;
				contColEsq 	= 0;
				resetar 	= 0;
				Revive_Aliens(&listaAlien);
				Revive_Bar(&listaBar);
				Destroi_Tiros(vetorTiros ,&contTiros ,3);
				Destroi_Tiros(vetorTirosA,&contTirosA,5);
				if ((!acabou)&&(!fechou))
				{
					wclear(jogo);
					nodelay(stdscr, FALSE);
					while (key != 's')
					{
						mvwprintw(jogo, janela_linha - 4, 5*(janela_coluna/6)/2 - 12 ,"Aperte s para continuar");
						imprime_reset(jogo,janela_linha,janela_coluna);
						key = getch();	
					}
				}	
				nodelay(stdscr, TRUE);
			} /*aqui acaba o while do jogo*/
			if (! fechou)
			{
				wclear(jogo);
				nodelay(stdscr, FALSE);
				while (key != 's')
				{
					mvwprintw(jogo, janela_linha - 4, 5*(janela_coluna/6)/2 - 10 ,"Aperte s para fechar");
					imprime_morte(jogo,janela_linha,janela_coluna);
					key = getch();
				}
			}
			
			/*sequencia de frees*/
			Free_Listas(&listaAlien,&listaBar);
			for (i=0 ; i<18 ; i++)
			{
				free(vetorspritesA[i]);
			}
			free(vetorspritesA);
			for (i=0 ; i<3 ; i++)
			{
				free(vetorTiros[i]);
			}
			free(vetorTiros);
			free(naveMae);
			for (i=0 ; i<5 ; i++)
			{
				free (vetorTirosA[i]);
			}
			free (vetorTirosA);
		}	/*aqui acaba o segundo if*/
		else if (key != 'q')
		{
			clear();
			endwin(); 
			printf("Erro: botao nao reconhecido :( \n"); 
		}
	}	/*aqui acaba o primeiro if*/
	else
		clear();
	endwin(	);
	return 0;
}
