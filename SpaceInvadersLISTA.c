#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define sprite1i1 " /+\\ "
#define sprite1i2 "/o-O\\"
#define sprite1i3 "\\+++/"
#define sprite1i5 "/O-o\\"
#define sprite2i1 " /W\\ "
#define sprite2i2 " \\0/ "
#define sprite2i3 "\\_H_/"
#define sprite2i5 " \\-/ "
#define sprite2i6 "/_H_\\"
#define sprite3i1 "d000b"
#define sprite3i2 "|8-8|"
#define sprite3i3 "/\\|/\\"
#define sprite3i5 "|8o8|"
#define sprite3i6 "\\/|\\/"

#define spriteJ1 " _/V\\_ "
#define spriteJ2 " >UwU< "

#define VIVO 1
#define MORTO 0
#define MORRENDO 2
#define EspacoAliensC 77	/* 7*11, onde 7 é o tamanho de coluna de cada alien e 11 é o número de aliens*/
#define EspacoAliensL 20	/* 4*5, onde 4 é o tamanho de linha de cada alien e 5 é o número de aliens*/
#define constTemp 40000

typedef struct t_alien
{
	int estado;
	int posi_l;
	int posi_c;
	struct t_alien *prox;
	struct t_alien *prev;
} t_alien;

typedef struct t_listaAlien
{
	t_alien *ini;
	t_alien *fim;
} t_listaAlien;

typedef struct t_tiro
{
	int lin;
	int col;
} t_tiro;

void InicializaSpritesAliens(char **vetors)	/*essa funcao inicaliza as sprites dos aliens em um vetor com esses sprites*/
{
	strcpy(vetors[0],sprite1i1);
	strcpy(vetors[1],sprite1i2);
	strcpy(vetors[2],sprite1i3);
	strcpy(vetors[3],sprite1i1);
	strcpy(vetors[4],sprite1i5);
	strcpy(vetors[5],sprite1i3);
	strcpy(vetors[6],sprite2i1);
	strcpy(vetors[7],sprite2i2);
	strcpy(vetors[8],sprite2i3);
	strcpy(vetors[9],sprite2i1);
	strcpy(vetors[10],sprite2i5);
	strcpy(vetors[11],sprite2i6);
	strcpy(vetors[12],sprite3i1);
	strcpy(vetors[13],sprite3i2);
	strcpy(vetors[14],sprite3i3);
	strcpy(vetors[15],sprite3i1);
	strcpy(vetors[16],sprite3i5);
	strcpy(vetors[17],sprite3i6);
}

void insere_fim(t_listaAlien *l,int estado,int linha,int coluna)
{
	t_alien *new = (t_alien *) malloc (sizeof(t_alien));
	if (! ( new == NULL ))					/*insere no fiz para manter a ordem da lista*/
	{
		new->prox = l->fim;
		new->prev = l->fim->prev;
		new->estado = estado;
		new->posi_l = linha;
		new->posi_c = coluna;
		l->fim->prev->prox = new;
		l->fim->prev = new;
	}
	else
	{
		free(new);
	}
}								

void InicializaListaAliens(t_listaAlien* listaAliens)	/*Inicializa a lista que contém os aliens*/
{
	t_alien *ini = (t_alien *) malloc (sizeof(t_alien));
        t_alien *fim = (t_alien *) malloc (sizeof(t_alien));
                                                                
        if ((ini == NULL) || (fim == NULL))			
        {
        	free (ini);
        	free (fim);
        }
	else
	{                                                        
        	ini->prox = fim;
        	fim->prev = ini;
                                                                
        	ini->prev = NULL;
        	fim->prox = NULL;
       	                                                         
        	listaAliens->ini = ini;						
        	listaAliens->fim = fim;
		int i;
		int j;
		for ( i=0 ; i<5 ; i++ )				/*insere os aliens com suas devidas posiçoes e estado VIVO na lista*/
		{
			for ( j=0 ; j<11 ; j++ )
			{
				insere_fim(listaAliens,VIVO,i,j);
			}	
		}
	}
}

void ImprimeAliensPOSATUAL(t_listaAlien *listaAlien,int linha,int coluna,char **vetorS,WINDOW *jogo,int *intercalaS)
{
	int tipo;
	t_alien *p = listaAlien->ini->prox;
	while (p->prox != NULL)
	{
		tipo = (p->posi_l + 1)/2;
		if (*intercalaS == 1)
		{
			if (p->estado == VIVO)
			{
				mvwprintw(jogo , linha+4*p->posi_l   , coluna+7*p->posi_c , vetorS[tipo*6]  );
				mvwprintw(jogo , linha+4*p->posi_l+1 , coluna+7*p->posi_c , vetorS[tipo*6+1]);
				mvwprintw(jogo , linha+4*p->posi_l+2 , coluna+7*p->posi_c , vetorS[tipo*6+2]);
			}
		}
		else
		{
			if (p->estado == VIVO)
			{
				mvwprintw(jogo , linha+4*p->posi_l   , coluna+7*p->posi_c , vetorS[tipo*6+3]);
				mvwprintw(jogo , linha+4*p->posi_l+1 , coluna+7*p->posi_c , vetorS[tipo*6+4]);
				mvwprintw(jogo , linha+4*p->posi_l+2 , coluna+7*p->posi_c , vetorS[tipo*6+5]);
			}
		}
		p = p->prox;
	}
	wrefresh(jogo);
	*intercalaS = (*intercalaS + 1)%2;
}

void ImprimeJogador(int linhaJogador,int colunaJogador,WINDOW *jogo)
{
	mvwprintw(jogo , linhaJogador   , colunaJogador-1 , spriteJ1);
	mvwprintw(jogo , linhaJogador+1 , colunaJogador-1 , spriteJ2);
}

void Verifica_Tiro(t_tiro *tiro,int linha_atual,int coluna_atual)
{
	if ((tiro->lin < linha_atual+20) && (tiro->lin >= linha_atual))
	{
		if ((tiro->col >= coluna_atual)&&(tiro->col < coluna_atual+77))
		{
			if ( !(tiro->col - coluna_atual % 7 == 0 ))
			{
				int i,j;
				i = ( tiro->lin - linha_atual  ) / 5;
				j = ( tiro->col - coluna_atual ) / 11;
				if ( Verifica_Alien(i,j,lista_Alien) )
				{
					Mata_Alien (i,j,lista_Alien) ;
					return 1;
				}
			}
		}
	}
	else if (linha_tiro < linha_atual)
	{
		/*adicionar teste da nave mãe*/
	}
	return 0;
}

void Atira (int linhaJogador,int colunaJogador,int *contTiros,t_tiro *vetorTiros)
{
	vetorTiros[*contTiros]->lin = linhaJogador - 1;
	vetorTiros[*contTiros]->col = colunaJogador + 3;
	*contTiros++;
}

void Organiza_Tiros (t_tiro *vetorTiros, int i);
{
	int j;
	for (j=i ; j<2 ; j++)
	{
		vetorTiros[j]->lin = vetor[j+1]->lin;
		vetorTiros[j]->col = vetor[j+1]->col;
	}
	vetorTiros[j]->lin = 0;
	vetorTiros[j]->col = 0;
}

void ImprimeTiros (t_tiro *vetorTiros, WINDOW *jogo)
{
	int i;
	for ( i=0 ; i<3 ; i++ )
	{
		if (! ((vetorTiros[i]->lin == 0) && (vetorTiros[i]->col == 0)))
		{
			mvwprintw(jogo , vetorTiros[i]->lin , vetorTiros[i]->col , "|");
		}
	}
}

void MoveJogador(int *atirou,int contTiros,int *colunaJogador,char key,int janela_coluna,int *acabou)
{
	if(key == ' ') 
	{
		if (contTiros < 3)
		{
			atirou = 1;
		}
	}
	else if(key == 'a')
	{
		if (*colunaJogador-1 > 0)
 		*colunaJogador = *colunaJogador - 1;
  	}
	else if (key == 'd') 
	{
		if (*colunaJogador + 6 < (janela_coluna - (janela_coluna/6)))
		*colunaJogador = *colunaJogador + 1;
	}
	else if (key == 'q') 
	{
		*acabou = 1;
		endwin();
	}						
}

int main ()
{
	char **vetorspritesA;
	vetorspritesA = (char **) malloc (18*sizeof(char*));		/*aloca espaço pra um vetor de sprites de aliens e poe os sprites nele*/
	int i;
	for ( i=0 ; i<18 ; i++)
	{
		vetorspritesA[i] = (char *) malloc (6*sizeof(char));
	}
	InicializaSpritesAliens (vetorspritesA);

	t_listaAlien listaAlien;					/*inicializa os aliens na lista*/
	InicializaListaAliens (&listaAlien);

	t_tiro *vetorTiros;
	vetorTiros = (t_tiro *) malloc (3*sizeof(t_tiro));
	for (i=0 ; i<3 ; i++)
	{
		vetorTiros[i]->lin = 0;
		vetorTiros[i]->col = 0;
	}

	initscr();			/*coisa que tinha no moodle*/
	noecho();
	nodelay(stdscr, TRUE);	
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	
	int janela_linha,janela_coluna;
	getmaxyx(stdscr , janela_linha , janela_coluna);

	WINDOW *jogo = newwin (janela_linha , janela_coluna-(janela_coluna/6) , 0 , 0);
	WINDOW *score = newwin(janela_linha , (janela_coluna/6) , 0 , janela_coluna-(janela_coluna/6));
	refresh();

	box(score,0,0);
	box(jogo,0,0);
	wrefresh(jogo);
	wrefresh(score);
	
	int linhaAliens = 1;
	int colunaAliens = 1;
	int linhaJogador = janela_linha-3;
	int colunaJogador = janela_coluna/2;
	int intercalaS = 1;
	int indo = 1;
	int indice = 0;
	int acabou = 0;
	int atirou = 0;
	int contTiros = 0;
	char key ;

	while (indice <= constTemp)
	{
		key = getch();
		if (indice == 0)					/*quando os aliens se movem*/
		{
			wclear(jogo);
			if (indo)
			{
				if (colunaAliens+EspacoAliensC == janela_coluna-(janela_coluna/6))
				{
					linhaAliens++;
					ImprimeAliensPOSATUAL(&listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
					colunaAliens--;
					indo = 0;
				}
				else if (colunaAliens+EspacoAliensC < janela_coluna-(janela_coluna/6))
				{
					ImprimeAliensPOSATUAL(&listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
					colunaAliens++;
				}					/*ate aqui lida com os aliens indo pra direita*/
			}
			else
			{
                     		if (colunaAliens == 1)
                      		{
                      			linhaAliens++;
                       			ImprimeAliensPOSATUAL(&listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
                       			colunaAliens++;
                       			indo = 1;
                       		}
                       		else if (colunaAliens+EspacoAliensC < janela_coluna-(janela_coluna/6))
                       		{
                       			ImprimeAliensPOSATUAL(&listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
                      			colunaAliens--;
                       		}
			}	
		}

               	MoveJogador(&atirou , contTiros , &colunaJogador , key , janela_coluna , &acabou);
		ImprimeJogador(linhaJogador , colunaJogador , jogo);
		
		if (atirou)
		{
			Atira(linhaJogador , colunaJogador , &contTiros , vetorTiros);
			atirou = 0;
		}
		
		ImprimeTiros(vetorTiros,jogo);
		
		if (contTiros > 0)
		{
			for ( i=0 ; i<contTiros ; i++)
			{
				if (Verifica_Tiro(vetorTiros[i],linhaAliens,colunaAliens))
				{
					Organiza_Tiros(vetorTiros,i);
					contTiros--;
				}
				else
				{
					vetorTiros[i]->lin--;
				}
			}	
		}
		
		box(jogo,0,0);
		wrefresh(jogo);
		indice++;
		if ((indice == constTemp)&&(! acabou))
			indice=0;
	}
	endwin();
	return 0;
}