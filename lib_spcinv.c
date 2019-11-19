#include "lib_spvinv.h"

void Inicializa_Sprites_Aliens(char **vetors)	/*essa funcao inicaliza as sprites dos aliens em um vetor com esses sprites*/
{
	strcpy(vetors[0] ,sprite1i1);
	strcpy(vetors[1] ,sprite1i2);
	strcpy(vetors[2] ,sprite1i3);
	strcpy(vetors[3] ,sprite1i1);
	strcpy(vetors[4] ,sprite1i5);
	strcpy(vetors[5] ,sprite1i3);
	strcpy(vetors[6] ,sprite2i1);
	strcpy(vetors[7] ,sprite2i2);
	strcpy(vetors[8] ,sprite2i3);
	strcpy(vetors[9] ,sprite2i1);
	strcpy(vetors[10],sprite2i5);
	strcpy(vetors[11],sprite2i6);
	strcpy(vetors[12],sprite3i1);
	strcpy(vetors[13],sprite3i2);
	strcpy(vetors[14],sprite3i3);
	strcpy(vetors[15],sprite3i1);
	strcpy(vetors[16],sprite3i5);
	strcpy(vetors[17],sprite3i6);
}

void Insere_Fim_Aliens(t_listaAlien *l,int estado,int linha,int coluna)
{
	t_alien *new = (t_alien *) malloc (sizeof(t_alien));
	if (! ( new == NULL ))					/*insere no fim para manter a ordem da lista*/
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
		free(new);
}								

void Inicializa_Lista_Aliens(t_listaAlien* listaAliens)	/*Inicializa a lista que contém os aliens*/
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
				Insere_Fim_Aliens(listaAliens,VIVO,i,j);
		}
	}
}

void Insere_Fim_Bar(t_listaBar *l,int janela_linha,int janela_coluna,int i)
{
	t_bar *new = (t_bar *) malloc (sizeof(t_bar));
	if (! ( new == NULL ))	
	{
		new->prox = l->fim;
		new->prev = l->fim->prev;;
		l->fim->prev->prox = new;
		l->fim->prev = new;

		new->linha = janela_linha - 10;
		new->coluna = ((janela_coluna)/5)*i;

		new->matriz = (int **) malloc (4*sizeof(int *));
		int j;
		int k;
		for (j=0 ; j<4 ; j++)
		{
			new->matriz[j] = (int *) malloc (5*sizeof(int));
			for (k=0 ; k<5 ; k++)
			{
				if (((j == 0) && ((k==0) || (k==4))) || ((j==3)&& ((k>0) && (k<4))))
					new->matriz[j][k] = MORTO;
				else
					new->matriz[j][k] = VIVO;
			}
		}
	}
	else
		free(new);
}								

void Inicializa_Lista_Bar(t_listaBar *listaBar,int janela_linha,int janela_coluna)
{
	t_bar *ini = (t_bar *) malloc (sizeof(t_bar));
	t_bar *fim = (t_bar *) malloc (sizeof(t_bar));
	
	if ((ini == NULL) || (fim == NULL))
	{
		free(ini);
		free(fim);
	}
	else
	{
		ini->prox = fim;
		fim->prev = ini;

		ini->prev = NULL;
		fim->prox = NULL;

		listaBar->ini = ini;
		listaBar->fim = fim;
		int i;
		for ( i=1 ; i<5 ; i++)
		{
			Insere_Fim_Bar(listaBar,janela_linha,janela_coluna,i);
		}
	}
}

void Imprime_Aliens_POS_ATUAL(t_listaAlien *listaAlien,int linha,int coluna,char **vetorS,WINDOW *jogo,int *intercalaS) /*função que imprime os aliens de acordo com uma posição atual*/
{
	int tipo;
	t_alien *p = listaAlien->ini->prox;
	while (p->prox != NULL)
	{
		tipo = (p->posi_l + 1)/2;	/*essa conta serve para determinar o tipo de alien da linha, para saber qual sprite imprimir*/
		if (*intercalaS == 1)		/*esse intercala serve para intercalar os sprites que os aliens ficam trocando*/
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
		if (p->estado == MORRENDO)
		{
			mvwprintw(jogo , linha+4*p->posi_l   , coluna+7*p->posi_c , spriteEX1);
	                mvwprintw(jogo , linha+4*p->posi_l+1 , coluna+7*p->posi_c , spriteEX2);
                        mvwprintw(jogo , linha+4*p->posi_l+2 , coluna+7*p->posi_c , spriteEX3);
			p->estado = MORTO;
		}
		p = p->prox;
	}
	wrefresh(jogo);
	*intercalaS = (*intercalaS + 1)%2;	/*altera o intercala para a proxima impressao*/
}

void Imprime_Jogador(int linhaJogador,int colunaJogador,WINDOW *jogo)	/*imprime a nave do jogador*/
{
	mvwprintw(jogo , linhaJogador   , colunaJogador-1 , spriteJ1);
	mvwprintw(jogo , linhaJogador+1 , colunaJogador-1 , spriteJ2);
}

int Verifica_Alien(int i,int j,t_listaAlien *listaAlien)
{
	int k;
	t_alien *p = listaAlien->ini->prox;
	for ( k=0 ; k < i*11 + j ; k++ )	/*esse laço chega no alien requerido pela chamada da função*/
		p = p->prox;

	if (p->estado == VIVO)			/*se o alien requerido estiver vivo, ele retorna 1, se não, retorna 0*/
		return 1;
	else
		return 0;
}

void Mata_Alien(int i,int j,t_listaAlien *listaAlien)
{
	int k;
	t_alien *p = listaAlien->ini->prox;
	for ( k=0 ; k < i*11 + j ; k++ )	/*chega no alien requerido*/
		p = p->prox;

	p->estado = MORRENDO;			/*machuca o alien requerido*/
}

void Organiza_Tiros (t_tiro ***vetorTiros, int i,int tam)	/*função que organiza um vetor de tiros baseado em seu tamanho*/		
{
	int j;
	for (j=i ; j<tam-1 ; j++)					/*quando um tiro some, ou por que chegou em cima da tela, ou por que*/
	{								/*acertou algo, a funcao tira o buraco que fica no vetor de tiros*/
		(*vetorTiros)[j]->lin = (*vetorTiros)[j+1]->lin;
		(*vetorTiros)[j]->col = (*vetorTiros)[j+1]->col;
	}
	(*vetorTiros)[j]->lin = 0;
	(*vetorTiros)[j]->col = 0;
}

int Verifica_Tiro(t_tiro *tiro,int linha_atual,int coluna_atual,t_listaAlien *listaAlien,t_mae *naveMae,t_listaBar *listaBar,int *score,t_tiro **vetorTirosA,int *contTirosA)	/*função que verifica se o tiro da nave vai fazer algo além de subir*/
{
	int i;
	for (i=0 ; i<5 ; i++)
	{
		if (((tiro->lin == vetorTirosA[i]->lin + 1)||(tiro->lin == vetorTirosA[i]->lin))&&(tiro->col == vetorTirosA[i]->col))
		{
			Organiza_Tiros(&vetorTirosA,i,5);
			*contTirosA = *contTirosA - 1;
			return 1;	
		}
	}
	if (tiro->lin == 1)	/*se tiver chegado no topo*/
		return 1;
	else if ((tiro->lin < linha_atual+20) && (tiro->lin >= linha_atual))					/*se tiver nas linhas dos aliens*/
	{
		if ((tiro->col >= coluna_atual)&&(tiro->col < coluna_atual+77))					/*se tiver na coluna dos aliens*/
		{
			if ( !(tiro->col - coluna_atual % 7 == 0 )||(tiro->col - coluna_atual  % 7 == 6))	/*se tiver nos aliens*/
			{
				int j;
				i = ( tiro->lin - linha_atual  ) / 4;						/*calcula qual aliens deve ser analisado*/
				j = ( tiro->col - coluna_atual ) / 7;
				if ( Verifica_Alien(i,j,listaAlien) )						/*vê se o alien ta vivo*/
				{
					Mata_Alien (i,j,listaAlien) ;						/*mata o alien*/
					*score = *score + 10;
					return 1;
				}
			}
		}
	}
	else if (tiro->lin < linha_atual)						/*se o tiro estiver depois da linha dos aliens*/
	{
		if ((tiro->lin < 5)&&(tiro->lin > 1))					/*se ele estiver nas linhas da nave mãe*/
		{
			if ((tiro->col > naveMae->col)&&(tiro->col < naveMae->col + 9))	/*se ele estiver nas colunas da nave mãe*/
			{
				naveMae->estado = MORRENDO;
				*score = *score + 200;
				return 1;
			}
		}
	}
	else if ((tiro->lin >= listaBar->ini->prox->linha)&&(tiro->lin <= listaBar->ini->prox->linha + 3)) /*se o tiroestá nas linhas das barreiras*/
	{
		t_bar *p;
		p = listaBar->ini->prox;
		for (i=0 ; i<4 ; i++)
		{
			if ((tiro->col >= p->coluna)&&(tiro->col <= p->coluna + 4))     /*se tiver nas colunas das barreiras*/
			{
				if (p->matriz[tiro->lin - p->linha][tiro->col - p->coluna]) /*se a barreira estiver "VIVA"*/
				{
					p->matriz[tiro->lin - p->linha][tiro->col - p->coluna] = MORTO; /*"MATA" a barreira*/
					return 1;
				}
			}
			p = p->prox;
		}
	}
	return 0;
}

int Verifica_Tiro_A(t_tiro *tiro,int janela_linha,int linhaJogador,int colunaJogador,int *acabou,t_listaBar *listaBar)	/*função que verifica se o tiro do alien vai fazer algo além de descer*/
{
	if (tiro->lin == janela_linha)		/*se chegar no fundo da tela*/
		return 1;
	else if ((tiro->lin < linhaJogador+2)&&(tiro->lin >= linhaJogador))		/*se estiver nas linhas do jogador*/
	{
		if ((tiro->col < colunaJogador+5)&&(tiro->col >= colunaJogador))	/*se estiver nas colunas do jogador*/
		{
			*acabou = 1;
			return 1;
		}
	}
	else if ((tiro->lin >= listaBar->ini->prox->linha)&&(tiro->lin <= listaBar->ini->prox->linha + 3)) /*se estiver na linha das barreiras*/
        {
        	int i;
        	t_bar *p;
        	p = listaBar->ini->prox;
        	for (i=0 ; i<4 ; i++)
        	{
        		if ((tiro->col >= p->coluna)&&(tiro->col <= p->coluna + 4))     /*se estiver nas colunas da barreira*/
        		{
        			if (p->matriz[tiro->lin - p->linha][tiro->col - p->coluna]) /*se a barreira estiver "VIVA"*/
        			{
        				p->matriz[tiro->lin - p->linha][tiro->col - p->coluna] = MORTO; /*"MATA" a barreira*/
        				return 1;
        			}
        		}
        		p = p->prox;
        	}
        }
	return 0;
}

void Atira (int linhaJogador,int colunaJogador,int *contTiros,t_tiro **vetorTiros)	/*função que faz o jogador atirar*/
{
	(vetorTiros[*contTiros])->lin = linhaJogador - 1;		/*adiciona um tiro com a determinada posicao no vetor de tiros*/
	(vetorTiros[*contTiros])->col = colunaJogador + 2;
	*contTiros = *contTiros + 1;
}

void Imprime_Tiros (t_tiro **vetorTiros, WINDOW *jogo)		/*função que imprime os tiros do jogador*/
{
	int i;
	for ( i=0 ; i<3 ; i++ )
	{
		if (! ((vetorTiros[i]->lin == 0) && (vetorTiros[i]->col == 0)))			/*se o tiro existir, apaga o anterior e imprime na*/
		{										/*posição atual*/
			mvwprintw(jogo , vetorTiros[i]->lin + 1 , vetorTiros[i]->col , " ");
			mvwprintw(jogo , vetorTiros[i]->lin     , vetorTiros[i]->col , "|");
		}
	}
}

void Imprime_TirosA (t_tiro **vetorTirosA, WINDOW *jogo)		/*função que imprime os tiros dos aliens*/
{
	int i;
	for ( i=0 ; i<5 ; i++)
	{
		if (! ((vetorTirosA[i]->lin == 0) && (vetorTirosA[i]->col == 0)))		/*se o tiro existir, apaga o anterior e imprime na posição atual*/
		{
			mvwprintw(jogo , vetorTirosA[i]->lin - 1 , vetorTirosA[i]->col , " ");
			mvwprintw(jogo , vetorTirosA[i]->lin     , vetorTirosA[i]->col , "$");
		}
	}
}

void Move_Jogador(int *atirou,int contTiros,int *colunaJogador,char key,int janela_coluna,int *fechou)	/*função que move o jogador, verifica se ele quer atirar e se ele quer fechar o jogo*/
{
	if(key == ' ') 
	{
		if (contTiros < 3)	/*limite de tiros*/
			*atirou = 1;
	}
	else if(key == 'a')
	{
		if (*colunaJogador-1 > 0)
 		*colunaJogador = *colunaJogador - 1;
  	}
	else if (key == 'd') 
	{
		if (*colunaJogador + 6 < (janela_coluna - (janela_coluna/constDivTela)))
		*colunaJogador = *colunaJogador + 1;
	}
	else if (key == 'q') 		/*sai do jogo*/
	{
		*fechou = 1;
		endwin();
	}						
}

void Administra_Impressao_Aliens (WINDOW *jogo, int *colunaAliens, int *linhaAliens, int janela_coluna, int janela_linha, char **vetorspritesA, int *intercalaS, t_listaAlien *listaAlien, int *indo,int contColEsq,int contColDir,int *perAlAtual)
{			/*função feita para limpar a main que cuida da parte de impressão dos aliens*/
	wclear(jogo);
	if (*indo)		/*se estiver indo pra direita*/
	{
		if (*colunaAliens+EspacoAliensC == janela_coluna-(janela_coluna/constDivTela) + 7*contColDir)	/*se estiver no canto direito*/
		{
			*linhaAliens = *linhaAliens + 1;
			Imprime_Aliens_POS_ATUAL(listaAlien,*linhaAliens,*colunaAliens,vetorspritesA,jogo,intercalaS);
			*colunaAliens = *colunaAliens - 1;
			*indo = 0;
			*perAlAtual = *perAlAtual / constDivPer;
		}
		else if (*colunaAliens+EspacoAliensC < janela_coluna-(janela_coluna/constDivTela) + 7*contColDir)
		{
			Imprime_Aliens_POS_ATUAL(listaAlien,*linhaAliens,*colunaAliens,vetorspritesA,jogo,intercalaS);
			*colunaAliens = *colunaAliens + 1;
		}
	}
	else			/*se estiver indo pra esquerda*/
	{
		if (*colunaAliens == 1 - 7*contColEsq)		/*se estiver no canto esquerdo*/
		{
			*linhaAliens = *linhaAliens + 1;
			Imprime_Aliens_POS_ATUAL(listaAlien,*linhaAliens,*colunaAliens,vetorspritesA,jogo,intercalaS);
			*colunaAliens = *colunaAliens + 1;
			*indo = 1;
			*perAlAtual = *perAlAtual / constDivPer;
		}
		else if (*colunaAliens+EspacoAliensC < janela_coluna-(janela_coluna/constDivTela) + 7*contColDir)
		{
			Imprime_Aliens_POS_ATUAL(listaAlien,*linhaAliens,*colunaAliens,vetorspritesA,jogo,intercalaS);
			*colunaAliens = *colunaAliens - 1;
		}
	}
}

void Verifica_Colunas (int *contColDir, int *contColEsq, t_listaAlien *listaAliens)	/*função que verifica as colunas mortas de aliens para aumentar o quanto os aliens devem andar na tela*/
{
	int i;
	int j = 0;
	int colMorta = 1;
	t_alien *p;
	if (*contColEsq < 11)
	{
		p = listaAliens->ini->prox;		/*verifica as coluna da esquerda*/
		for ( i=0 ; i < *contColEsq ; i++ )
			p = p->prox;

		if (p->estado == VIVO)
       		 	colMorta = 0;
		while ((colMorta)&&(j<4))
		{
			for ( i=0 ; i<11 ; i++ )
				p = p->prox;

			if (p->estado == VIVO)
               		 	colMorta = 0;
			j++;
		}
		if (colMorta)
			*contColEsq = *contColEsq + 1;
	}
	
	if (*contColDir < 11)
	{
		p = listaAliens->ini->prox;			/*verifica as coluna da direita*/
		colMorta = 1;
		j = 0;
		for (i=0 ; i < 10 - *contColDir ; i++ )
			p = p->prox;

		if (p->estado == VIVO)
			colMorta = 0;
		while ((colMorta)&&(j<4))
		{
			for ( i=0 ; i<11 ; i++ )
				p = p->prox;

			if (p->estado == VIVO)
				colMorta = 0;
			j++;
		}
		if (colMorta)
			*contColDir = *contColDir + 1;
	}
}

void Revive_Aliens (t_listaAlien *listaAliens)	/*função que revive os aliens, usada quando o jogo reseta*/
{
	int i;
	t_alien *p = listaAliens->ini->prox;
	for (i=0 ; i<55 ; i++)
	{
		p->estado = VIVO;
		p = p->prox;
	}
}

void Destroi_Tiros (t_tiro **vetorTiros,int *contTiros,int tam)	/*função que destroi os tiros de um vetor de tiros baseado em seu tamanho*/
{
	int i;
	for ( i=0 ; i<tam ; i++)
	{
		vetorTiros[i]->lin = 0;
		vetorTiros[i]->col = 0;
	}
	*contTiros = 0;
}

void Imprime_Mae (t_mae *naveMae,int *intercalaS,WINDOW *jogo)		/*função que imprime a nave mãe*/
{
	if (naveMae->estado == VIVO)
	{
		if (*intercalaS)	/*aproveita a variavel que intercala os aliens para intecalar seus sprites também*/
		{
			mvwprintw(jogo,linhaMAE  ,naveMae->col,spriteM11);
			mvwprintw(jogo,linhaMAE+1,naveMae->col,spriteM21);
			mvwprintw(jogo,linhaMAE+2,naveMae->col,spriteM31);
		}
		else
		{
			mvwprintw(jogo,linhaMAE  ,naveMae->col,spriteM12);
               		mvwprintw(jogo,linhaMAE+1,naveMae->col,spriteM22);
               		mvwprintw(jogo,linhaMAE+2,naveMae->col,spriteM32);
		}
	}
	else if (naveMae->estado == MORRENDO)
	{
		mvwprintw(jogo,linhaMAE  ,naveMae->col, spriteEX4);
	        mvwprintw(jogo,linhaMAE+1,naveMae->col, spriteEX5);
	        mvwprintw(jogo,linhaMAE+2,naveMae->col, spriteEX6);
		naveMae->estado = MORTO;
	}
}

void Alien_Atira(WINDOW *jogo,int *contTirosA,int random,int linhaAlien,int colunaAlien,t_tiro **vetorTirosA,t_listaAlien *listaAlien)	/*função que faz um alien aleatorio atirar, se ele estiver vivo*/
{
	t_alien *p = listaAlien->ini->prox;
	int i;
	for (i=0 ; i<random ; i++)
		p = p->prox;
	if (p->estado == VIVO)
	{
		int j;
		i = random/11;
		j = random%11;
		vetorTirosA[*contTirosA]->col = colunaAlien + j*7;
		vetorTirosA[*contTirosA]->lin = linhaAlien + i*4;
		*contTirosA = *contTirosA + 1;
	}
}

void Administra_Tiros (int *contTiros,int *contTirosA,t_tiro **vetorTiros,t_tiro **vetorTirosA,t_listaAlien *listaAlien,t_mae *naveMae,int *acabou,int colunaAliens,int linhaAliens,int colunaJogador,int linhaJogador,int janela_linha,t_listaBar *listaBar,int *score)
{		/*uma função feita para limpar a main, que cuida dos tiros do jogador e dos aliens*/
	int i;
	if (*contTiros > 0)
        {
        	for ( i=0 ; i<*contTiros ; i++ )
        	{
        		if (Verifica_Tiro(vetorTiros[i],linhaAliens,colunaAliens,listaAlien,naveMae,listaBar,score,vetorTirosA,contTirosA))
        		{
        			Organiza_Tiros(&vetorTiros,i,3);
        			*contTiros = *contTiros - 1;
        		}
        		else
        			vetorTiros[i]->lin--;
        	}	
        }

        if (*contTirosA > 0)
        {
        	for ( i=0 ; i<*contTirosA ; i++ )
        	{
        		if (Verifica_Tiro_A(vetorTirosA[i],janela_linha,linhaJogador,colunaJogador,acabou,listaBar))
        		{
        			Organiza_Tiros(&vetorTirosA,i,5);
        			*contTirosA = *contTirosA - 1;
        		}
        		else
        			vetorTirosA[i]->lin++;
        	}
        }													
}

void Imprime_Barreiras (t_listaBar *listaBar,WINDOW *jogo)
{
	t_bar *p = listaBar->ini->prox;
	int i;
	int j;
	int k;
	for (i=0 ; i<4 ; i++)           /*passa por todas as barreiras*/
	{
		for (j=0 ; j<4 ; j++)       /*passa por todas as linhas de cada barreira*/
		{
			for (k=0 ; k<5 ; k++)   /*passa por todas as colunas de cada barreira*/
			{
				if (p->matriz[j][k])    /*se o pedaço da barreira estiver "VIVO"*/
					mvwprintw(jogo, p->linha + j , p->coluna + k , "A");
			}
		}
		p = p->prox;
	}
}

void Destroi_Linha_Bar(t_listaBar *listaBar, int linha)
{
	t_bar *p = listaBar->ini->prox;
	int i,j;
	for (i=0 ; i<4 ; i++)       /*passa por todas as barreiras*/
	{
		for (j=0 ; j<5 ; j++)   /*passa por todas as colunas de cada barreira*/
		{
			p->matriz[linha][j] = MORTO;
		}
		p = p->prox;
	}
}

void Verifica_Linha_Aliens(t_listaAlien *listaAliens,int *contLin)
{
	t_alien *p;
	p = listaAliens->ini->prox;
	int i;
	int alienVivo = 0;
	for (i=0 ; i< 44-(*contLin)*11 ; i++)   /*chega na atual última linha de aliens*/
		p = p->prox;
	i = 0;
	while ((i < 11)&&(! alienVivo))         /*passa por todos os aliens da linha e, se algum estiver vivo, não aumenta o contador*/
	{
		if (p->estado == VIVO)
			alienVivo = 1;
		i = i + 1;
		p = p->prox;
	}
	if (! alienVivo)
		*contLin = *contLin + 1;
}

