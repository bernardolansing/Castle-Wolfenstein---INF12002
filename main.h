#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

#define largura 800
#define altura 300
#define ppl_width 20
#define ppl_height 48
#define hud_height altura / 7

#define qnt_inimigos 1


struct Fonte {
	Font alpha_beta;
	Font mecha;
	Font jupiter_crash;
};

struct Partida {
	int pontuacao;
	char legenda[50];
};

struct Jogador {
	int posx;
	int posy;
	int vidas;
	int municao;
	int facas;
	char direcao;
};

struct Inimigo {
	int posx;
	int posy;
	int vivo; // vivo (1) ou morto (0).
	char direcao;
};

struct Bau {
	char conteudo;  // tipo de item
	int posx;
	int posy;
	int estado;  // aberto (1) ou fechado (0).
	int qnt;  // quantidade de itens
};

struct Porta {
	int posx;
	int posy;
	int liberada; // trancada (0) ou aberta (1).
};

struct Partida game;  // criação da partida
struct Jogador player;  // criação do player
struct Inimigo inimigos[qnt_inimigos];
struct Porta porta;
struct Fonte fonte;
struct Bau bau1;  // criação do baú

#endif
