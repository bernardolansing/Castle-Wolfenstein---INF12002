#include <raylib.h>
#include <string.h>
#include <main.h>

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