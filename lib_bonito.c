#include "lib_bonito.h"

/*#define SCORE1 " __   __   __   __   ___ "
#define SCORE2 "/__` /  ` /  \\ |__) |__  "
#define SCORE3 ".__/ \\__, \\__/ |  \\ |___ "*/

#define SCORE1 " __                    "
#define SCORE2 "/ _\\ ___ ___  _ __ ___ "
#define SCORE3 "\\ \\ / __/ _ \\| '__/ _ \\"
#define SCORE4 "_\\ \\ (_| (_) | | |  __/"
#define SCORE5 "\\__/\\___\\___/|_|  \\___|"
                                                                        
#define MENU01 "        ______                                                                                      "
#define MENU02 "       /      \\                                                                                     "
#define MENU03 "      |  $$$$$$\\  ______    ______    _______   ______                                              "
#define MENU04 "      | $$___\\$$ /      \\  |      \\  /       \\ /      \\                                             "
#define MENU05 "       \\$$    \\ |  $$$$$$\\  \\$$$$$$\\|  $$$$$$$|  $$$$$$\\                                            "
#define MENU06 "       _\\$$$$$$\\| $$  | $$ /      $$| $$      | $$    $$                                            "
#define MENU07 "      |  \\__| $$| $$__/ $$|  $$$$$$$| $$_____ | $$$$$$$$                                            "
#define MENU08 "       \\$$    $$| $$    $$ \\$$    $$ \\$$     \\ \\$$     \\                                            "
#define MENU09 "        \\$$$$$$ | $$$$$$$   \\$$$$$$$  \\$$$$$$$  \\$$$$$$$                                            "
#define MENU10 "                | $$                                                                                "
#define MENU11 "                | $$                                                                                "
#define MENU12 "                 \\$$                                                                                "
#define MENU13 "       ______                                     __                                                "
#define MENU14 "      |      \\                                   |  \\                                               "
#define MENU15 "       \\$$$$$$ _______  __     __  ______    ____| $$  ______    ______    _______                  "
#define MENU16 "        | $$  |       \\|  \\   /  \\|      \\  /      $$ /      \\  /      \\  /       \\                 "
#define MENU17 "        | $$  | $$$$$$$\\$$\\ /  $$ \\$$$$$$\\|  $$$$$$$|  $$$$$$\\|  $$$$$$\\|  $$$$$$$                 "
#define MENU18 "        | $$  | $$  | $$ \\$$\\  $$ /      $$| $$  | $$| $$    $$| $$   \\$$ \\$$    \\                  "
#define MENU19 "       _| $$_ | $$  | $$  \\$$ $$ |  $$$$$$$| $$__| $$| $$$$$$$$| $$       _\\$$$$$$\\                 "
#define MENU20 "      |   $$ \\| $$  | $$   \\$$$   \\$$    $$ \\$$    $$ \\$$     \\| $$      |       $$                 "
#define MENU21 "       \\$$$$$$ \\$$   \\$$    \\$     \\$$$$$$$  \\$$$$$$$  \\$$$$$$$ \\$$       \\$$$$$$$                  "
#define MENU22 "                                                                                                    "
#define MENU23 "                   ____.                                                                            "
#define MENU24 "                  |    | ____   _________ _______              ______                               "
#define MENU25 "                  |    |/  _ \\ / ___\\__  \\\\_  __ \\   ______   /  ___/                               "
#define MENU26 "              /\\__|    (  <_> ) /_/  > __ \\|  | \\/  /_____/   \\___ \\                                "
#define MENU27 "              \\________|\\____/\\___  (____  /__|              /____  >                               "
#define MENU28 "                             /_____/     \\/                       \\/                                "
#define MENU29 "                                                                                                    "
#define MENU30 "              ___________           .__                                                             "
#define MENU31 "              \\_   _____/___   ____ |  |__ _____ _______              ______                        "
#define MENU32 "               |    __)/ __ \\_/ ___\\|  |  \\\\__  \\\\_  __ \\   ______   / ____/                        "
#define MENU33 "               |     \\\\  ___/\\  \\___|   Y  \\/ __ \\|  | \\/  /_____/  < <_|  |                        "
#define MENU34 "               \\___  / \\___  >\\___  >___|  (____  /__|               \\__   |                        "
#define MENU35 "                   \\/      \\/     \\/     \\/     \\/                      |__|                        "
#define MENU36 "                                                                                                    "
#define MENU37 "                                                                                                    "     
#define MENU38 "                                                                                                    "

#define RESET01 " __________                                                                      "   
#define RESET02 " \\______   \\_______   ____ ___________ _______   ____             ______ ____    "
#define RESET03 "  |     ___/\\_  __ \\_/ __ \\\\____ \\__  \\\\_  __ \\_/ __ \\   ______  /  ___// __ \\   "
#define RESET04 "  |    |     |  | \\/\\  ___/|  |_> > __ \\|  | \\/\\  ___/  /_____/  \\___ \\\\  ___/   "
#define RESET05 "  |____|     |__|    \\___  >   __(____  /__|    \\___  >         /____  >\\___  >  "
#define RESET06 "                         \\/|__|       \\/            \\/               \\/     \\/   "
#define RESET07 "                                                                                 "
#define RESET08 "                       ___________ ____________                                  "
#define RESET09 "                       \\____ \\__  \\\\_  __ \\__  \\                                 "
#define RESET10 "                       |  |_> > __ \\|  | \\// __ \\_                               " 
#define RESET11 "                       |   __(____  /__|  (____  /                               "
#define RESET12 "                       |__|       \\/           \\/                                "
#define RESET13 "                                              .__                                "
#define RESET14 "           _____    _____________  _______  __|__| _____ _____                   "
#define RESET15 "           \\__  \\   \\____ \\_  __ \\/  _ \\  \\/  /  |/     \\\\__  \\                  " 
#define RESET16 "            / __ \\_ |  |_> >  | \\(  <_> >    <|  |  Y Y  \\/ __ \\_                "
#define RESET17 "           (____  / |   __/|__|   \\____/__/\\_ \\__|__|_|  (____  /                "
#define RESET18 "                \\/  |__|                     \\/        \\/     \\/                 "
#define RESET19 "                                             .___                                "
#define RESET20 "                   _______  ____   ____    __| _/____                            "
#define RESET21 "                   \\_  __ \\/  _ \\ /    \\  / __ |\\__  \\                           " 
#define RESET22 "                    |  | \\(  <_> )   |  \\/ /_/ | / __ \\_                         "
#define RESET23 "                    |__|   \\____/|___|  /\\____ |(____  /                         "
#define RESET24 "                                      \\/      \\/     \\/                          "

#define MORTE01 "________           .___                                                        "
#define MORTE02 "\\_____  \\   ______ |   | _______  _______    _________________   ____   ______ "
#define MORTE03 " /   |   \\ /  ___/ |   |/    \\  \\/ /\\__  \\  /  ___/  _ \\_  __ \\_/ __ \\ /  ___/ "
#define MORTE04 "/    |    \\\\___ \\  |   |   |  \\   /  / __ \\_\\___ (  <_> )  | \\/\\  ___/ \\___ \\  "
#define MORTE05 "\\_______  /____  > |___|___|  /\\_/  (____  /____  >____/|__|    \\___  >____  > "
#define MORTE06 "        \\/     \\/           \\/           \\/     \\/                  \\/     \\/  "
#define MORTE07 "         ____   ____                                                           "
#define MORTE08 "         \\   \\ /   /____   ____   ____  ________________    _____              "
#define MORTE09 "          \\   Y   // __ \\ /    \\_/ ___\\/ __ \\_  __ \\__  \\  /     \\             "
#define MORTE10 "           \\     /\\  ___/|   |  \\  \\__\\  ___/|  | \\// __ \\|  Y Y  \\            "
#define MORTE11 "            \\___/  \\___  >___|  /\\___  >___  >__|  (____  /__|_|  /            "
#define MORTE12 "                       \\/     \\/     \\/    \\/           \\/      \\/             "

#define PAUSA01 "* __________                               *"
#define PAUSA02 "* \\______   \\_____   __ __  ___________    *"
#define PAUSA03 "*  |     ___/\\__  \\ |  |  \\/  ___/\\__  \\   *"
#define PAUSA04 "*  |    |     / __ \\|  |  /\\___ \\  / __ \\_ *"
#define PAUSA05 "*  |____|    (____  /____//____  >(____  / *"
#define PAUSA06 "*                 \\/           \\/      \\/  *"
#define PAUSA07 "********************************************"

void imprime_score_e_arte (WINDOW *score,int tam_col)
{
        mvwprintw(score, 1, tam_col/2-11,SCORE1);
        mvwprintw(score, 2, tam_col/2-11,SCORE2);
        mvwprintw(score, 3, tam_col/2-11,SCORE3);
        mvwprintw(score, 4, tam_col/2-11,SCORE4);
        mvwprintw(score, 5, tam_col/2-11,SCORE5);
}

void imprime_menu (int janela_linha,int janela_coluna)
{
	int posi_linha = janela_linha/2 - 19;
	int posi_coluna = 5*(janela_coluna/6)/2 - 50;
	mvprintw (posi_linha   ,posi_coluna,MENU01);
	mvprintw (posi_linha+1 ,posi_coluna,MENU02);
	mvprintw (posi_linha+2 ,posi_coluna,MENU03);
	mvprintw (posi_linha+3 ,posi_coluna,MENU04);
	mvprintw (posi_linha+4 ,posi_coluna,MENU05);
	mvprintw (posi_linha+5 ,posi_coluna,MENU06);
	mvprintw (posi_linha+6 ,posi_coluna,MENU07);
	mvprintw (posi_linha+7 ,posi_coluna,MENU08);
	mvprintw (posi_linha+8 ,posi_coluna,MENU09);
	mvprintw (posi_linha+9 ,posi_coluna,MENU10);
	mvprintw (posi_linha+10,posi_coluna,MENU11);
	mvprintw (posi_linha+11,posi_coluna,MENU12);
	mvprintw (posi_linha+12,posi_coluna,MENU13);
	mvprintw (posi_linha+13,posi_coluna,MENU14);
	mvprintw (posi_linha+14,posi_coluna,MENU15);
	mvprintw (posi_linha+15,posi_coluna,MENU16);
	mvprintw (posi_linha+16,posi_coluna,MENU17);
	mvprintw (posi_linha+17,posi_coluna,MENU18);
	mvprintw (posi_linha+18,posi_coluna,MENU19);
	mvprintw (posi_linha+19,posi_coluna,MENU20);
	mvprintw (posi_linha+20,posi_coluna,MENU21);
	mvprintw (posi_linha+21,posi_coluna,MENU22);
	mvprintw (posi_linha+22,posi_coluna,MENU23);
	mvprintw (posi_linha+23,posi_coluna,MENU24);
	mvprintw (posi_linha+24,posi_coluna,MENU25);
	mvprintw (posi_linha+25,posi_coluna,MENU26);
	mvprintw (posi_linha+26,posi_coluna,MENU27);
	mvprintw (posi_linha+27,posi_coluna,MENU28);
	mvprintw (posi_linha+28,posi_coluna,MENU29);
	mvprintw (posi_linha+29,posi_coluna,MENU30);
	mvprintw (posi_linha+30,posi_coluna,MENU31);
	mvprintw (posi_linha+31,posi_coluna,MENU32);
	mvprintw (posi_linha+32,posi_coluna,MENU33);
	mvprintw (posi_linha+33,posi_coluna,MENU34);
	mvprintw (posi_linha+34,posi_coluna,MENU35);
	mvprintw (posi_linha+35,posi_coluna,MENU36);
	mvprintw (posi_linha+36,posi_coluna,MENU37);
	mvprintw (posi_linha+37,posi_coluna,MENU38);
}

void imprime_reset (WINDOW *jogo,int janela_linha,int janela_coluna)
{
	int posi_linha = janela_linha/2 - 12;
	int posi_coluna = 5*(janela_coluna/6)/2 - 45;
	mvwprintw (jogo, posi_linha   , posi_coluna,RESET01);
	mvwprintw (jogo, posi_linha+1 , posi_coluna,RESET02);
	mvwprintw (jogo, posi_linha+2 , posi_coluna,RESET03);
	mvwprintw (jogo, posi_linha+3 , posi_coluna,RESET04);
	mvwprintw (jogo, posi_linha+4 , posi_coluna,RESET05);
	mvwprintw (jogo, posi_linha+5 , posi_coluna,RESET06);
	mvwprintw (jogo, posi_linha+6 , posi_coluna,RESET07);
	mvwprintw (jogo, posi_linha+7 , posi_coluna,RESET08);
	mvwprintw (jogo, posi_linha+8 , posi_coluna,RESET09);
	mvwprintw (jogo, posi_linha+9 , posi_coluna,RESET10);
	mvwprintw (jogo, posi_linha+10, posi_coluna,RESET11);
	mvwprintw (jogo, posi_linha+11, posi_coluna,RESET12);
	mvwprintw (jogo, posi_linha+12, posi_coluna,RESET13);
	mvwprintw (jogo, posi_linha+13, posi_coluna,RESET14);
	mvwprintw (jogo, posi_linha+14, posi_coluna,RESET15);
	mvwprintw (jogo, posi_linha+15, posi_coluna,RESET16);
	mvwprintw (jogo, posi_linha+16, posi_coluna,RESET17);
	mvwprintw (jogo, posi_linha+17, posi_coluna,RESET18);
	mvwprintw (jogo, posi_linha+18, posi_coluna,RESET19);
	mvwprintw (jogo, posi_linha+19, posi_coluna,RESET20);
	mvwprintw (jogo, posi_linha+20, posi_coluna,RESET21);
	mvwprintw (jogo, posi_linha+21, posi_coluna,RESET22);
	mvwprintw (jogo, posi_linha+22, posi_coluna,RESET23);
	mvwprintw (jogo, posi_linha+23, posi_coluna,RESET24);
	wrefresh(jogo);
}

void imprime_morte (WINDOW *jogo,int janela_linha,int janela_coluna)
{
	int posi_linha  = (janela_linha/2)-6;
	int posi_coluna = 5*(janela_coluna/6)/2 - 40;
	mvwprintw (jogo, posi_linha   , posi_coluna,MORTE01);
	mvwprintw (jogo, posi_linha+1 , posi_coluna,MORTE02);
	mvwprintw (jogo, posi_linha+2 , posi_coluna,MORTE03);
	mvwprintw (jogo, posi_linha+3 , posi_coluna,MORTE04);
	mvwprintw (jogo, posi_linha+4 , posi_coluna,MORTE05);
	mvwprintw (jogo, posi_linha+5 , posi_coluna,MORTE06);
	mvwprintw (jogo, posi_linha+6 , posi_coluna,MORTE07);
	mvwprintw (jogo, posi_linha+7 , posi_coluna,MORTE08);
	mvwprintw (jogo, posi_linha+8 , posi_coluna,MORTE09);
	mvwprintw (jogo, posi_linha+9 , posi_coluna,MORTE10);
        mvwprintw (jogo, posi_linha+10, posi_coluna,MORTE11);
	mvwprintw (jogo, posi_linha+11, posi_coluna,MORTE12);
	wrefresh(jogo);
}

void imprime_pausa (WINDOW *jogo,int janela_linha,int janela_coluna)
{
	int posi_linha  = janela_linha/2 - 4;
	int posi_coluna = 5*(janela_coluna/6)/2 - 22;
	mvwprintw (jogo, posi_linha   , posi_coluna,PAUSA07);
        mvwprintw (jogo, posi_linha+1 , posi_coluna,PAUSA01);
        mvwprintw (jogo, posi_linha+2 , posi_coluna,PAUSA02);
        mvwprintw (jogo, posi_linha+3 , posi_coluna,PAUSA03);
        mvwprintw (jogo, posi_linha+4 , posi_coluna,PAUSA04);
        mvwprintw (jogo, posi_linha+5 , posi_coluna,PAUSA05);
        mvwprintw (jogo, posi_linha+6 , posi_coluna,PAUSA06);
        mvwprintw (jogo, posi_linha+7 , posi_coluna,PAUSA07);
	wrefresh(jogo);
}
