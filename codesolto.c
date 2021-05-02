// código solto esperando para ser disbtribuído pelos arquivos apropriados.

#include <raylib.h>
#include <string.h>
#include <codesolto.h>

#define largura 800
#define altura 300
#define ppl_width 20
#define ppl_height 48
#define hud_height altura / 7

/*struct Partida {
	int pontuacao;
	char legenda[50];
	Font alpha_beta;
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
*/

//struct Partida game;  // criação da partida
//struct Jogador player;  // criação do player


// movimenta o jogador pelo cenário
void mover_jogador() {

	if (IsKeyDown(KEY_UP)) {
		if (player.posy != 0) player.posy -= 2;
		player.direcao = 'C';
	}

	else if (IsKeyDown(KEY_DOWN)) {
		if (player.posy < altura - ppl_height - hud_height) player.posy += 2;
		player.direcao = 'B';
	}


	if (IsKeyDown(KEY_RIGHT)) {
		if (player.posx < largura - ppl_width) player.posx += 2;
		player.direcao = 'D';
	}

	else if (IsKeyDown(KEY_LEFT)) {
		if (player.posx != 0) player.posx -= 2;
		player.direcao = 'E';
	}
}

// movimenta o inimigo, perseguindo o jogador
void mover_inimigo(int *posx, int *posy, char *direcao) {
	if (player.posy > *posy) {
		*posy += 1;
		*direcao = 'C';
	}
	else if (player.posy < *posy) {
		*posy -= 1;
		*direcao = 'B';
	}

	if (player.posx > *posx) {
		*posx += 1;
		*direcao = 'D';
	}
	else if (player.posx < *posx) {
		*posx -= 1;
		*direcao = 'E';
	}
}

// verifica se o inimigo colidiu com o jogador
bool checar_colisao(struct Inimigo inimigo) {
	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	Rectangle box_inimigo = {inimigo.posx, inimigo.posy, ppl_width, ppl_height};

	return (CheckCollisionRecs(box_jogador, box_inimigo));
}

// responde se há um baú fechado por perto
bool bau_perto(struct Bau bau) {
	if (bau.estado) return false;  // retorna false caso o baú já tenha sido aberto
	
	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	Rectangle box_bau = {bau.posx, bau.posy, 65, 65};

	return (CheckCollisionRecs(box_jogador, box_bau));	
}

// marca o baú como fechado e dá ao jogador seus espólios
void loot_bau(char conteudo, int qnt, int *fechadura) {
	*fechadura = 1;  // define o baú como aberto (bau.estado = 1)

	switch (conteudo) {
		case 'M':
		player.municao += qnt;
		strcpy(game.legenda, "Voce abriu o bau e encontrou municao!");
		break;

		case 'V': player.vidas += qnt;
		strcpy(game.legenda, "Voce abriu o bau e ganhou uma vida!");
		break;

		case 'F': player.facas += qnt;
		strcpy(game.legenda, "Voce abriu o bau e encontrou facas!");
		break;

		case 'P': game.pontuacao += qnt;
		strcpy(game.legenda, "Voce abriu o bau e ganhou pontos extras!");
		break;
	}

	// dá 50 pontos por ter aberto o baú
	game.pontuacao += 50;
}

// desenha a tela da morte
void morte() {
	DrawRectangle(0, 0, largura, altura, (Color) {0, 0, 0, 210});
	DrawTextEx(game.alpha_beta, "Voce morreu!", (Vector2) {largura / 2, altura / 2}, 24, 5, ORANGE);
}


// determina qual é o passo (1, 2, 3 ou 4) que o personagem está dando
int selec_passo(int posicao) {
	posicao %= 240;
	
	if (posicao < 61) return 0;
	if (posicao < 121) return 1;
	if (posicao < 181) return 2;
	return 3;
}

// seleciona a imagem correta do jogador, de acordo com direção e passo, e a imprime
void draw_jogador() {
	int passo;
	Texture2D imgplayer;

	// carrega a imagem sob nome "player"
	switch (player.direcao) {
		
		case 'C':
		passo = selec_passo(player.posy);

		switch (passo) {
			case 0:
			imgplayer = LoadTexture("resources/player/player-up-4.png");
			break;

			case 1:
			imgplayer = LoadTexture("resources/player/player-up-1.png");
			break;

			case 2:
			imgplayer = LoadTexture("resources/player/player-up-2.png");
			break;

			case 3:
			imgplayer = LoadTexture("resources/player/player-up-3.png");
			break;
		}

		break;

		case 'B':
		passo = selec_passo(player.posy);

		switch (passo) {
			case 0:
			imgplayer = LoadTexture("resources/player/player-down-4.png");
			break;

			case 1:
			imgplayer = LoadTexture("resources/player/player-down-1.png");
			break;

			case 2:
			imgplayer = LoadTexture("resources/player/player-down-2.png");
			break;

			case 3:
			imgplayer = LoadTexture("resources/player/player-down-3.png");
			break;
		}

		break;

		case 'D':
		passo = selec_passo(player.posx);

		switch (passo) {
			case 0:
			imgplayer = LoadTexture("resources/player/player-right-4.png");
			break;

			case 1:
			imgplayer = LoadTexture("resources/player/player-right-1.png");
			break;

			case 2:
			imgplayer = LoadTexture("resources/player/player-right-2.png");
			break;

			case 3:
			imgplayer = LoadTexture("resources/player/player-right-3.png");
			break;
		}

		break;

		case 'E':
		passo = selec_passo(player.posx);

		switch (passo) {
			case 0:
			imgplayer = LoadTexture("resources/player/player-left-4.png");
			break;

			case 1:
			imgplayer = LoadTexture("resources/player/player-left-1.png");
			break;

			case 2:
			imgplayer = LoadTexture("resources/player/player-left-2.png");
			break;

			case 3:
			imgplayer = LoadTexture("resources/player/player-left-3.png");
			break;
		}

		break;
	}

	// Rectangle Playerbox = {player.posx, player.posy, 44, 53};  // define a caixa do jogador
	
	DrawTexture(imgplayer, player.posx, player.posy, RAYWHITE);
}

void draw_inimigo(struct Inimigo inimigo) {
	int passo;
	Texture2D imginimigo;

	switch (inimigo.direcao) {
		
		case 'C':
		passo = selec_passo(inimigo.posy);

		switch (passo) {
			case 0:
			imginimigo = LoadTexture("resources/enemy/enemy-up-4.png");
			break;

			case 1:
			imginimigo = LoadTexture("resources/enemy/enemy-up-1.png");
			break;

			case 2:
			imginimigo = LoadTexture("resources/enemy/enemy-up-2.png");
			break;

			case 3:
			imginimigo = LoadTexture("resources/enemy/enemy-up-3.png");
			break;
		}

		break;

		case 'B':
		passo = selec_passo(inimigo.posy);

		switch (passo) {
			case 0:
			imginimigo = LoadTexture("resources/enemy/enemy-down-4.png");
			break;

			case 1:
			imginimigo = LoadTexture("resources/enemy/enemy-down-1.png");
			break;

			case 2:
			imginimigo = LoadTexture("resources/enemy/enemy-down-2.png");
			break;

			case 3:
			imginimigo = LoadTexture("resources/enemy/enemy-down-3.png");
			break;
		}

		break;

		case 'D':
		passo = selec_passo(inimigo.posx);

		switch (passo) {
			case 0:
			imginimigo = LoadTexture("resources/enemy/enemy-right-4.png");
			break;

			case 1:
			imginimigo = LoadTexture("resources/enemy/enemy-right-1.png");
			break;

			case 2:
			imginimigo = LoadTexture("resources/enemy/enemy-right-2.png");
			break;

			case 3:
			imginimigo = LoadTexture("resources/enemy/enemy-right-3.png");
			break;
		}

		break;

		case 'E':
		passo = selec_passo(inimigo.posx);

		switch (passo) {
			case 0:
			imginimigo = LoadTexture("resources/enemy/enemy-left-4.png");
			break;

			case 1:
			imginimigo = LoadTexture("resources/enemy/enemy-left-1.png");
			break;

			case 2:
			imginimigo = LoadTexture("resources/enemy/enemy-left-2.png");
			break;

			case 3:
			imginimigo = LoadTexture("resources/enemy/enemy-left-3.png");
			break;
		}

		break;
	}

	DrawTexture(imginimigo, inimigo.posx, inimigo.posy, WHITE);
}

// imprime um baú na tela
void draw_bau(struct Bau bau) {
	Texture2D imgbau;
	
	if (!bau.estado) imgbau = LoadTexture("resources/scenario/chest-locked.png");
	else if (bau.estado) imgbau = LoadTexture("resources/scenario/chest-opened.png");

	DrawTexture(imgbau, bau.posx, bau.posy, WHITE);
}

// imprime a barra inferior do hud
void draw_hud() {
	int i;
	
	Rectangle hud = {0, altura * 6/7, largura, altura / 7};
	Font mecha = LoadFont("resources/fonts/mecha.png");
	

	DrawRectangle(hud.x, hud.y, hud.width, hud.height, (Color) {0, 0, 0, 200});

	// Impressão da munição ---------------------
	Vector2 posicao_municao = {30, altura - (hud.height / 2) - 10};
	Texture2D ammo = LoadTexture("resources/hud/bullet.png");
	DrawTextEx(mecha, "Municao:", posicao_municao, 16, 5, YELLOW);

	for (i = 0; i < player.municao; i++) {
		DrawTexture(ammo, 100 + 10 * i, altura - (hud.height / 2) - 13, WHITE);
	}

	// Impressão das facas ----------------------
	Vector2 posicao_facas = {120 + 10 * player.municao, posicao_municao.y};
	Texture2D faca = LoadTexture("resources/hud/knife.png");
	DrawTextEx(mecha, "Facas:", posicao_facas, 16, 5, YELLOW);

	for (i = 0; i < player.facas; i++) {
		DrawTexture(faca, posicao_facas.x + 44 + 10 * i, altura - (hud.height / 2) - 19, WHITE);
	}

	// Impressão das vidas ----------------------
	Vector2 posicao_vidas = {posicao_facas.x + 72 + 10 * player.facas, posicao_facas.y};
	Texture2D coracao = LoadTexture("resources/hud/heart.png");
	DrawTextEx(mecha, "Vidas:", posicao_vidas, 16, 5, YELLOW);

	for (i = 0; i < player.vidas; i++) {
		DrawTexture(coracao, posicao_vidas.x + 54 + 30 * i, altura - (hud.height / 2) - 12, WHITE);
	}

	// Impressão da legenda ---------------------
	Vector2 posicao_legenda = {420, posicao_municao.y};
	DrawTextEx(mecha, game.legenda, posicao_legenda, 16, 5, RAYWHITE);

	// Impressão da pontuação -------------------
	Vector2 posicao_pontuacao = {20, 10};
	//TextFormat("Pontuacao: %i", game.pontuacao);
	DrawTextEx(mecha, TextFormat("Pontuacao: %i", game.pontuacao), posicao_pontuacao, 16, 5, RAYWHITE);
}

void draw() {

	BeginDrawing();

	ClearBackground(DARKPURPLE);

	draw_hud();
	draw_bau(bau1);
	draw_jogador();
	draw_inimigo(inimigo1);

	EndDrawing();
}


int main() {
	// int pontuacao = 0, *p_pontos = &pontuacao;
	
	// INICIALIZAÇÃO DA PARTIDA
	game.pontuacao = 0;
	game.legenda[0] = '\0';
	game.alpha_beta = LoadFont("resources/fonts/alpha-beta.png");
	
	// INICIALIZAÇÃO DO JOGADOR
	player.posx = 400;
	player.posy = 150;
	player.vidas = 3;
	player.municao = 3;
	player.facas = 2;
	player.direcao = 'E';

	// INICIALIZAÇÃO DE UM BAÚ
	bau1.estado = 0;
	bau1.posx = 100;
	bau1.posy = 75;
	bau1.conteudo = 'M';
	bau1.qnt = 2;

	// INICIALIZAÇÃO DE UM INIMIGO
	inimigo1.posx = 700;
	inimigo1.posy = 70;
	inimigo1.vivo = 1;
	inimigo1.direcao = 'E';


	InitWindow(largura, altura, "Castle Wolfenstein");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		mover_jogador();
		mover_inimigo(&inimigo1.posx, &inimigo1.posy, &inimigo1.direcao);

		if (bau_perto(bau1) && IsKeyPressed(KEY_E)) {
			loot_bau(bau1.conteudo, bau1.qnt, &bau1.estado);
		}

		draw();
		
		if (checar_colisao(inimigo1)) {
			double hora_morte = GetTime();

			while (GetTime() <= hora_morte + 3 && !WindowShouldClose()) morte();
		}
	}


	return 0;
}
