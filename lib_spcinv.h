#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "lib_bonito.h"

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

#define spriteM11 "   /*\\  "
#define spriteM21 " /*0-0*\\"
#define spriteM31 " \\+x+x+/"
#define spriteM12 "   /*\\  "
#define spriteM22 " /*-o-*\\"
#define spriteM32 " \\x+x+x/"

#define spriteEX1 "\\ | /"
#define spriteEX2 "- 0 -"
#define spriteEX3 "/ | \\"

#define spriteEX4 " \\  |  /"
#define spriteEX5 " -  0  -"
#define spriteEX6 " /  |  \\"

#define spriteJ1 " _/V\\_ "
#define spriteJ2 " >UwU< "

#define VIVO 1
#define MORTO 0
#define MORRENDO 2
#define EspacoAliensC 77	/* 7*11, onde 7 é o tamanho de coluna de cada alien e 11 é o número de aliens*/
#define EspacoAliensL 20	/* 4*5, onde 4 é o tamanho de linha de cada alien e 5 é o número de aliens*/
#define constTemp 40000
#define constDivTela 6
#define constDivPer 1.05
#define linhaMAE 2

typedef struct t_alien		/*o tipo alien possui seu estado (VIVO, MORTO ou MORRENDO), sua posição e o proximo alien e o anterior*/
{
	int estado;
	int posi_l;
	int posi_c;
	struct t_alien *prox;
	struct t_alien *prev;
} t_alien;

typedef struct t_listaAlien	/*lista duplamente encadeada onde os nodos sao tipo alien*/
{
	t_alien *ini;
	t_alien *fim;
} t_listaAlien;

typedef struct t_tiro		/*tipo tiro possui sua posição*/
{
	int lin;
	int col;
} t_tiro;

typedef struct t_mae		/*tipo mae para a nave mae*/
{
	int estado;
	int col;
} t_mae;

typedef struct t_bar
{
	int linha;
	int coluna;
	int **matriz;
	struct t_bar *prox;
	struct t_bar *prev;
} t_bar;

typedef struct t_listaBar
{
	t_bar *ini;
	t_bar *fim;
} t_listaBar; 

void Inicializa_Sprites_Aliens (char **vetors);
/*põe os sprites dos aliens em um vetor de strings "vetors"*/

void Insere_Fim_Aliens (t_listaAlien *l,int estado,int linha,int coluna);
/*insere no final da lista "l" de aliens com um dado estado(MORTO,VIVO...), uma linha e uma coluna*/

void Inicializa_Lista_Aliens (t_listaAlien *listaAliens);
/*faz uma lista "listaAliens" com todos os aliens, chamando a Insere_Fim_Aliens*/

void Insere_Fim_Bar (t_listaBar *l,int janela_linha,int janela_coluna,int i);
/*insere no final da lista "l" de barreiras, usando o tamanho da tela e com "i" representando qual barreira é (primeira,segunda...)*/

void Inicializa_Lista_Bar (t_listaBar *listaBar,int janela_linha,int janela_coluna);
/*faz uma lista "listaBar" de barreiras usando o tamanho da tela, chamando a Insere_Fim_Bar*/

void Imprime_Aliens_POS_ATUAL (t_listaAlien *listaAlien,int linha,int coluna,char **vetorS,WINDOW *jogo, int *intercalaS);
/*imprime os aliens da "listaAlien", baseado em na posição atual do canto superior esquerdo ("linha" e "coluna"), usando o vetor de sprites "vetorS", a variável que troca os sprites "intercalaS", na tela "jogo"*/

void Imprime_Jogador(int linhaJogador,int colunaJogador,WINDOW *jogo);
/*imprime a nave do jogador baseado na posição "linhaJogador" e "colunaJogador" na tela "jogo"*/

int Verifica_Alien(int i,int j,t_listaAlien *listaAlien);
/*verifica se o alien da lista "listaAlien" que fica na linha "i" e na coluna "j" está vivo. Se está, retorna 1, se não, retorna 0*/

void Mata_Alien(int i,int j,t_listaAlien *listaAlien);
/*muda o estado do alien da lista "listaAlien" que fica na linha "i" e na coluna "j" para MORRENDO*/

void Organiza_Tiros (t_tiro ***vetorTiros, int i,int tam);
/*organiza o vetor de tiros "vetorTiros" à partir do tiro "i" até o "tamanho-1", trazendo os tiros pra casa anterior do vetor e colocando 0 e 0 na posição do último, tirando buracos*/

int Verifica_Tiro(t_tiro *tiro,int linha_atual,int coluna_atual,t_listaAlien *listaAlien,t_mae *naveMae,t_listaBar *listaBar,int *score,t_tiro **vetorTirosA,int *contTirosA);
/*verifica se o tiro "tiro" faz algo além de só subir. A função retorna 1 se esse tiro: mata um alien, destrói uma barreira, destrói um tiro de alien, mata a nave mãe ou chega no topo da tela. A função retorna 0 nos outros casos*/

int Verifica_Tiro_A(t_tiro *tiro,int janela_linha,int linhaJogador,int colunaJogador,int *acabou,t_listaBar *listaBar);
/*verifica se o tiro "tiro" do alien faz algo além de descer. A função retorna 1 se o tiro: chegar no fundo da tela, se acertar o jogador ou acertar uma barreira. Retorna 0 nos outros casos*/

void Atira (int linhaJogador,int colunaJogador,int *contTiros,t_tiro **vetorTiros);
/*põe um tiro no vetor de tiros "vetorTiros" baseado na posição do jogador e aumenta o contador de tiros*/

void Imprime_Tiros (t_tiro **vetorTiros, WINDOW *jogo);
/*imprime os tiros do jogador usando o vetor de tiros "vetorTiros" na tela "jogo"*/

void Imprime_TirosA (t_tiro **vetorTirosA, WINDOW *jogo);
/*imprime os tiros dos aliens usando o vetor de tiros "vetorTirosA" na tela "jogo"*/

void Move_Jogador(int *atirou,int contTiros,int *colunaJogador,char key,int janela_coluna,int *fechou);
/*função que faz os comandos do jogador: move, faz ele atirar e fecha o jogo*/

void Administra_Impressao_Aliens (WINDOW *jogo, int *colunaAliens, int *linhaAliens, int janela_coluna, int janela_linha, char **vetorspritesA, int *intercalaS, t_listaAlien *listaAlien, int *indo,int contColEsq,int contColDir,int *perAlAtual);
/*função feita para "limpar a main" que administra toda a parte de imprimir os aliens*/

void Verifica_Colunas (int *contColDir, int *contColEsq, t_listaAlien *listaAliens);
/*função que verifica as colunas de aliens mortos na esquerda e na direita, aumentando os contadores caso encontre uma nova coluna totalmente morta. Ela é usada para definir o quão longe os aliens vão na tela*/

void Revive_Aliens (t_listaAlien *listaAliens);
/*revive os aliens de uma lista "listaAliens", usada quando o jogo vai pra uma nova rodada*/

void Destroi_Tiros (t_tiro **vetorTiros,int *contTiros,int tam);
/*destrói os tiros de um vetor de tiros "vetorTiros" baseado no seu tamanho "tam" e zera o "contTiros"*/

void Imprime_Mae (t_mae *naveMae,int *intercalaS,WINDOW *jogo);
/*função que imprime a nave mãe "naveMae", intercalando seu sprite com "intercalaS" na tela "jogo"*/

void Alien_Atira(WINDOW *jogo,int *contTirosA,int random,int linhaAlien,int colunaAlien,t_tiro **vetorTirosA,t_listaAlien *l);
/*faz um alien aleatório atirar se ele estiver vivo*/

void Administra_Tiros (int *contTiros,int *contTirosA,t_tiro **vetorTiros,t_tiro **vetorTirosA,t_listaAlien *listaAlien,t_mae *naveMae,int *acabou,int colunaAliens,int linhaAliens,int colunaJogador,int linhaJogador,int janela_linha,t_listaBar *listaBar,int *score);
/*função feita para "limpar a main" que administra toda a parte dos tiros do jogador e dos aliens*/

void Imprime_Barreiras (t_listaBar *listaBar,WINDOW *jogo);
/*função que imprime as barreiras da lista de barreiras "listaBar" na tela "jogo"*/

void Destroi_Linha_Bar(t_listaBar *listaBar, int linha);
/*destrói uma linha inteira "linha" das barreiras da lista de barreiras "listaBar"*/

void Verifica_Linha_Aliens(t_listaAlien *listaAliens,int *contLin);
/*verifica se a atual última linha de aliens da "listaAliens" está inteiramente morta e, caso esteja, aumenta o contador de linhas "contLin"*/


