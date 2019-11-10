#include <ncurses.h>
#include <stdio.h>

void imprime_score_e_arte (WINDOW *score,int tam_col);

void imprime_menu (int janela_linha,int janela_coluna);

void imprime_reset (WINDOW *jogo,int janela_linha,int janela_coluna);

void imprime_morte (WINDOW *jogo,int janela_linha,int janela_coluna);

void imprime_pausa (WINDOW *jogo,int janela_linha,int janela_coluna);
