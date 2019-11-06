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
	int estado;
	int posi_l;
	int posi_c;
	t_alien *prox;
	t_alien *prev;
} *t_alien;

typedef struct t_listaA
	t_alien *ini;
	t_alien *fim;
} *t_listaA;

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

int insere_fim_lista(t_lista *l,int estado,int linha,int coluna)
{
	t_nodo *new = (t_nodo *) malloc (sizeof(t_nodo));
	if (! ( new == NULL ))
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

void InicializaListaAliens(t_alien* listaAliens)	/*Inicializa a lista que contém os aliens*/
{
	t_nodo *ini = (t_nodo *) malloc (sizeof(t_nodo));
        t_nodo *fim = (t_nodo *) malloc (sizeof(t_nodo));
                                                                
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
       	                                                         
        	l->ini = ini;						
        	l->fim = fim;
		int i;
		int j;
		for ( i=0 ; i<5 ; i++ )
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
	t_alien *p = l->ini->prox;
	while (p->prox != NULL)
	{
		tipo = (i+1)/2;
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
				mvwprintw(jogo , linha+4*p->posi_l+2 , coluna+7*p->posi_C , vetorS[tipo*6+5]);
			}
		}
		p = p->prox;
	}
	wrefresh(jogo);
	*intercalaS = (*intercalaS + 1)%2;
}

void ImprimeJogador(int linhaJogador,int colunaJogador,WINDOW *jogo)
{
	mvwprintw(jogo,linhaJogador,colunaJogador-1,spriteJ1);
	mvwprintw(jogo,linhaJogador+1,colunaJogador-1,spriteJ2);
}

void MoveJogador(int *colunaJogador,char key,int janela_y)
{
	if(key == ' ') 
	{
	}
	else if(key == 'a')
	{
		if (*colunaJogador-1 > 0)
 		*colunaJogador = *colunaJogador - 1;
  	}
	else if (key == 'd') 
	{
		if (*colunaJogador + 6 < (janela_y - (janela_y/6)))
		*colunaJogador = *colunaJogador + 1;
	}
	else if (key == 'q') 
	{
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

	t_listaAlien listaAlien;
	InicializaListaAliens (&listaAlien);
	

	initscr();			/*coisa que tinha no moodle*/
	noecho();
	nodelay(stdscr, TRUE);	
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	
	int janela_linha,janela_coluna;
	getmaxyx(stdscr , janela_linha , janela_coluna);
	WINDOW *jogo = newwin (janela_linha , janela_coluna-(janela_coluna/6) , 0 , 0);
	refresh();
	WINDOW *score = newwin(janela_linha , (janela_coluna/6) , 0 , janela_coluna-(janela_coluna/6));

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
	char key ;

	while (indice <= constTemp)
	{
		key = getch();
		if (indice == 0)					/*quando os aliens se movem*/
		{
			wclear(jogo);
			if (indo)
			{
				if (colunaAliens+EspacoAliensC == janela_y-(janela_y/6))
				{
					linhaAliens++;
					ImprimeAliensPOSATUAL(listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
					colunaAliens--;
					indo = 0;
				}
				else if (colunaAliens+EspacoAliensC < janela_y-(janela_y/6))
				{
					ImprimeAliensPOSATUAL(listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
					colunaAliens++;
				}					/*ate aqui lida com os aliens indo pra direita*/
			}
			else
			{
                     		if (colunaAliens == 1)
                      		{
                      			linhaAliens++;
                       			ImprimeAliensPOSATUAL(listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
                       			colunaAliens++;
                       			indo = 1;
                       		}
                       		else if (colunaAliens+EspacoAliensC < janela_y-(janela_y/6))
                       		{
                       			ImprimeAliensPOSATUAL(listaAlien,linhaAliens,colunaAliens,vetorspritesA,jogo,&intercalaS);
                      			colunaAliens--;
                       		}
			}	
		}
		/*if (ind % 2 == 0)*/					/*quando o jogador pode se mover*/
                /*{*/
                	MoveJogador(&colunaJogador,key,janela_y);
			ImprimeJogador(linhaJogador,colunaJogador,jogo);
                /*}*/							
		box(jogo,0,0);
		wrefresh(jogo);
		ind++;
		if (ind == constTemp)
			ind=0;
	}
	endwin();
	return 0;
}
