#include "lib_lista.h"
#include <stdio.h>
#include <stdlib.h>

int inicializa_lista (t_lista *l)
{
	t_nodo *ini = (t_nodo *) malloc (sizeof(t_nodo));
	t_nodo *fim = (t_nodo *) malloc (sizeof(t_nodo));

	if ((ini == NULL) || (fim == NULL))			/*se o malloc não funcionar*/
	{
		free (ini);
		free (fim);
		return 0;
	}

	ini->chave = 0;						/*inicia o ini e o fim*/
	fim->chave = 0;

	ini->prox = fim;
	fim->prev = ini;

	ini->prev = NULL;
	fim->prox = NULL;

	l->ini = ini;						/*inicia a lista em si*/
	l->fim = fim;
	l->atual = NULL;
	l->tamanho = 0;
	return 1;						
}

int lista_vazia (t_lista *l)
{
	if (l->tamanho != 0)
	{
		return 0;
	}
	return 1;
}

void destroi_lista(t_lista *l)
{
	if (l->tamanho != 0)
	{
		t_nodo *p = l->ini->prox;
		while ( p->prox != NULL)		/*destroi elementos intermediarios*/
		{
			p = p->prox;

			p->prev->chave = 0;
			p->prev->prev = NULL;
			p->prev->prox = NULL;
			free (p->prev);
		}
		l->tamanho = 0;
	}
	l->ini->prox = NULL;			/*destrói ini e fim*/
	free (l->ini);
	l->fim->prev = NULL;
	free (l->fim);
	l->ini = NULL;
	l->fim = NULL;
}

int insere_inicio_lista(int item, t_lista *l)
{
	t_nodo *new = (t_nodo *) malloc (sizeof(t_nodo));
	if ( new == NULL )					/*caso o malloc não funcionar*/
	{
		return 0;
	}
	
	l->ini->prox->prev = new;				/*arruma os ponteiros*/
	new->prox = l->ini->prox;
	new->prev = l->ini;
	new->chave = item;
	l->ini->prox = new;
	l->tamanho ++;
	return 1;
}

int tamanho_lista(int *tam, t_lista *l)
{
	*tam = l->tamanho;
	return 1;
}

int insere_fim_lista(int item, t_lista *l)
{
	t_nodo *new = (t_nodo *) malloc (sizeof(t_nodo));
	if ( new == NULL )
	{
		return 0;
	}
	new->prox = l->fim;
	new->prev = l->fim->prev;
	new->chave = item;
	l->fim->prev->prox = new;
	l->fim->prev = new;
	l->tamanho++;
	return 1;
}								

int insere_ordenado_lista(int item, t_lista *l)
{
	t_nodo *new = (t_nodo *) malloc (sizeof(t_nodo));
	if (new == 0)
	{
		return 0;
	}
	t_nodo *p;
        p = l->ini->prox;
	while ((p->prox != NULL) && (p->chave < item))		/*vai até o final ou até o elemento for menor*/
	{
		p = p->prox;
	}
	new->prox = p;
	new->prev = p->prev;
	p->prev->prox = new;
	p->prev = new;
	new->chave = item;
	l->tamanho++;
	return 1;
}

int remove_inicio_lista(int *item, t_lista *l)
{
	l->ini->prox = l->ini->prox->prox;		/*o prox do ini recebe o segundo elemento*/
	l->ini->prox->prev->prev = NULL;		/*o prev do primeiro elemento recebe nulo*/
	*item = l->ini->prox->prev->chave;
	l->ini->prox->prev->chave = 0;			/*a chave do primeiro elemento recebe nulo*/
	l->ini->prox->prev->prox = NULL;		/*o prox do primeiro elemento recebe nulo*/
	free (l->ini->prox->prev);			/*free no primeiro elemento*/
	l->ini->prox->prev = l->ini;			/*o prev do segundo elemento recebe o ini*/
	l->tamanho--;
	return 1;
}

int remove_fim_lista(int *item, t_lista *l)
{
	l->fim->prev = l->fim->prev->prev;		/*praticamente o mesmo processo de cima, mas invertido*/
	l->fim->prev->prox->prox = NULL;
	*item = l->fim->prev->prox->chave;
	l->fim->prev->prox->chave = 0;
	l->fim->prev->prox->prev = NULL;
	free (l->fim->prev->prox);
	l->fim->prev->prox = l->fim;
	l->tamanho--;
	return 1;
}

int remove_item_lista(int chave, int *item, t_lista *l)
{
	t_nodo *p;
	p = l->ini->prox;
	while ((p->prox != NULL) && (p->chave != chave))
	{
		p = p->prox;
	}						/*quando esse while acabar, ou o p->chave é igual à */
	if (p->chave != chave)					/*chave, ou está no final*/
	{
		return 0;
	}
	else
	{
		*item = chave;
		p->prox->prev = p->prev;
		p->prev->prox = p->prox;
		p->prev = NULL;
		p->prox = NULL;
		p->chave = 0;
		free (p);
		l->tamanho--;
		return 1;
	}
}

int pertence_lista(int chave, t_lista *l)
{
	t_nodo *p;
	p = l->ini->prox;
	while ((p->prox != NULL) && (p->chave != chave))
	{
		p = p->prox;
	}
	if ((p->chave == chave)&&(p->prox != NULL))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int inicializa_atual_inicio(t_lista *l)
{
	if (l->ini->prox == l->fim)
	{
		return 0;
	}
	l->atual = l->ini->prox;
	return 1;
}

int inicializa_atual_fim(t_lista *l)
{
	if (l->fim->prev == l->ini)
	{
		return 0;
	}
	l->atual = l->fim->prev;
	return 1;
}

void incrementa_atual(t_lista *l)
{
	l->atual = l->atual->prox;
	if (l->atual == l->fim)
	{
		l->atual = NULL;
	}
}

void decrementa_atual(t_lista *l)
{
	l->atual = l->atual->prev;
	if (l->atual == l->ini)
	{
		l->atual = NULL;
	}
}

int consulta_item_atual(int *item, t_lista *l)
{							/*mudei o nome da lista pra l, pois acredito que o*/
	if (l->atual == NULL)				/*"atual" do .h original foi um erro e acaba confundindo*/
	{
		return 0;
	}
	*item = l->atual->chave;
	return 1;
}

int remove_item_atual(int *item, t_lista *l)
{
	if (l->atual == NULL)
	{
		return 0;
	}
	*item = l->atual->chave;
	l->atual->prox->prev = l->atual->prev;
	l->atual->prev = NULL;
	l->atual = l->atual->prox;
	l->atual->prev->prox->prox = NULL;
	l->atual->prev->prox->chave = 0;
	free(l->atual->prev->prox);
	l->atual->prev->prox = l->atual;
	if (l->atual == l->fim)
	{
		l->atual = NULL;
	}
	l->tamanho--;
	return 1;
}
