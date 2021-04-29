#include <raylib.h>
#include <string.h>
#include <draw.h>

#define largura 800
#define altura 300
#define ppl_width 20
#define ppl_height 48
#define hud_height altura / 7

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

void draw_bau(struct Bau bau) {
	Texture2D imgbau;
	
	if (!bau.estado) imgbau = LoadTexture("resources/scenario/chest-locked.png");
	else if (bau.estado) imgbau = LoadTexture("resources/scenario/chest-opened.png");

	DrawTexture(imgbau, bau.posx, bau.posy, WHITE);
}

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
