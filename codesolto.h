#include <raylib.h>

struct Partida {
	int pontuacao;
	char legenda[50];
	Font alpha_beta;
	Font mecha;
//	alpha_beta = LoadFont("resources/fonts/alpha-beta.png");
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

struct Inimigo inimigo1;

struct Bau {
	char conteudo;  // tipo de item
	int posx;
	int posy;
	int estado;  // aberto (1) ou fechado (0).
	int qnt;  // quantidade de itens
};

struct Bau bau1;  // criação do baú

struct Porta {
	int posx;
	int posy;
	int liberada; // trancada (0) ou aberta (1).
};
