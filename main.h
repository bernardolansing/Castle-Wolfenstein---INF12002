#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

#define largura 800
#define altura 300
#define ppl_width 20
#define ppl_height 48
#define hud_height altura / 7

#define qnt_inimigos 1
#define qnt_facas 5  // contado com facas dentro de baús


struct Fonte {
	Font alpha_beta;
	Font mecha;
	Font jupiter_crash;
};

struct Partida {
	int pontuacao;
	char legenda[50];
	double horalegenda;
	int seletor_facas;
	int level;
	bool executar_menu;
};

struct Jogador {
	int posx;
	int posy;
	int vidas;
	int municao;
	int facas;
	char direcao;
	double horadisparo;
};

struct Faca {
	char direcao;
	int ar;  // em trajetória (1) ou guardada/caída (0).
	int posx;
	int posy;
	Vector2 drop;
	Rectangle hitbox;
};

struct Inimigo {
	int posx;
	int posy;
	int vivo; // vivo (1) ou morto (0).
	char direcao;
	double horamorte;
	Rectangle hitbox;
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
struct Inimigo inimigos[10];
struct Porta porta;
struct Fonte fonte;
struct Bau baus[10];  // criação do baú
struct Faca facas[10];
int acessos = 1;
#endif
