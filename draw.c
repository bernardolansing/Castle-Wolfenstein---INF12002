#ifndef DRAW_C
#define DRAW_C

#include <raylib.h>
#include <string.h>
#include "main.h"
#include "highscores.c"

// desenha a tela da morte
void morte() {
	DrawRectangle(0, 0, largura, altura, (Color) {0, 0, 0, 210});
	DrawTextEx(fonte.alpha_beta, "Voce morreu!", (Vector2) {largura / 2, altura / 2}, 30, 5, ORANGE);
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

	if (GetTime() - player.horadisparo < 0.5) {
		switch (player.direcao) {
			case 'C': imgplayer = LoadTexture("resources/player/player-up-shoot.png"); break;
			case 'B': imgplayer = LoadTexture("resources/player/player-down-shoot.png"); break;
			case 'D': imgplayer = LoadTexture("resources/player/player-right-shoot.png"); break;
			case 'E': imgplayer = LoadTexture("resources/player/player-left-shoot.png"); break;
		}
	}

	// carrega a imagem sob nome "imgplayer"
	else switch (player.direcao) {

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

// carrega a imagem do inimigo e a imprime
void draw_inimigo(struct Inimigo inimigo) {
	if (!inimigo.vivo) return;

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

	DrawTexture(imginimigo, inimigo.posx - 10, inimigo.posy - 15, WHITE);
}

// imprime o inimigo morto
void draw_inimigo_morto(struct Inimigo inimigo) {
	Texture2D imginimigo;

	if (GetTime() - inimigo.horamorte < 0.3) imginimigo = LoadTexture("resources/enemy/dying-1.png");
	else if (GetTime() - inimigo.horamorte < 0.6) imginimigo = LoadTexture("resources/enemy/dying-2.png");
	else if (GetTime() - inimigo.horamorte < 0.9) imginimigo = LoadTexture("resources/enemy/dying-3.png");
	else if (GetTime() - inimigo.horamorte < 1.2) imginimigo = LoadTexture("resources/enemy/dying-4.png");
	else imginimigo = LoadTexture("resources/enemy/dying-5.png");

	DrawTexture(imginimigo, inimigo.posx, inimigo.posy, LIGHTGRAY);
}

// imprime a porta
void draw_porta() {
	Texture2D imgporta;

	if (porta.liberada) imgporta = LoadTexture("resources/scenario/door-opened.png");
	else imgporta = LoadTexture("resources/scenario/door-locked.png");

	DrawTexture(imgporta, porta.posx, porta.posy, WHITE);
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
	DrawTextEx(mecha, TextFormat("Pontuacao: %i", game.pontuacao), posicao_pontuacao, 16, 5, RAYWHITE);
}

void draw_faca(struct Faca faca) {
	int rotacao = 0;
	Color cor;
	Texture2D imgfaca = LoadTexture("resources/scenario/knife.png");
	Vector2 posicao = {faca.posx, faca.posy};

	switch (faca.direcao) {
		case 'C': rotacao = -90; break;
		case 'B': rotacao = 90; break;
		case 'D': rotacao = 0; break;
		case 'E': rotacao = 180; break;
	}

	if (faca.ar) cor = WHITE;
	else {cor = DARKGRAY; rotacao += 45;}

	DrawTextureEx(imgfaca, posicao, rotacao, 0.5, cor);
}

void draw() {
	int i;

	BeginDrawing();

	ClearBackground(DARKPURPLE);

	draw_hud();
	for (i = 0; i < 10; i++) draw_bau(baus[i]);
	draw_porta();

	for (i = 0; i < 10; i++) draw_faca(facas[i]);

	for (i = 0; i < 10; i++)  {
		if (inimigos[i].vivo) draw_inimigo(inimigos[i]);
		else draw_inimigo_morto(inimigos[i]);
	}

	draw_jogador();

	EndDrawing();
}

void draw_level_cleared() {
	double hora = GetTime();

	while (GetTime() - hora < 3) {
		BeginDrawing();

		ClearBackground(SKYBLUE);
		DrawText("Fase concluida!", 280, 135, 22, DARKBLUE);

		EndDrawing();
	}
}

void derrota() {
	double hora = GetTime();

	while (GetTime() - hora < 3) {
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText("VOCE FOI DERROTADO", 280, 135, 22, YELLOW);

		EndDrawing();

		if (WindowShouldClose()) CloseWindow();  // evita que o jogo fique congelado
	}

	gameover();
	//return;
}

void vitoria() {
	double hora = GetTime();

	while (GetTime() - hora < 3) {
		BeginDrawing();

		ClearBackground(PINK);
		DrawText("VOCE VENCEU!!!", 280, 135, 28, ORANGE);

		EndDrawing();

		if (WindowShouldClose()) CloseWindow();  // evita que o jogo fique congelado

		gameover();
	}
}

#endif
