#include <raylib.h>
#include <main.h>
#include <motion.c>
#include <draw.c>
#include <collision.c>
#include <string.h>


int main() {
	int i, seletor_facas = 0;

	// INICIALIZAÇÃO DA PARTIDA E DAS FONTES
	game.pontuacao = 0;
	game.legenda[0] = '\0';
	fonte.alpha_beta = LoadFont("resources/fonts/alpha-beta.png");
	//fonte.mecha = LoadFont("resources/fonts/mecha.png");
	fonte.jupiter_crash = LoadFont("resources/fonts/jupyter-crash.png");

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
	inimigos[0].posx = 700;
	inimigos[0].posy = 70;
	inimigos[0].vivo = 1;
	inimigos[0].direcao = 'E';
	inimigos[0].hitbox.width = ppl_width;
	inimigos[0].hitbox.height = ppl_height;

	// INICIALIZAÇÃO DA PORTA
	porta.liberada = 0;
	porta.posx = 700;
	porta.posy = 210;

	// INICIALIZAÇÃO DAS FACAS
	for (i = 0; i < player.facas; i++) {
		facas[i].ar = 0;
		facas[i].hitbox.width = 29;
		facas[i].hitbox.height = 10;
		facas[i].posx = largura * 2;
		facas[i].posy = altura * 2;
	}

	InitWindow(largura, altura, "Castle Wolfenstein");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		// reset da legenda
		if (GetTime() - game.horalegenda > 3) memset(game.legenda, 0, 50);
		
		mover_jogador();
		for (i = 0; i < qnt_inimigos; i++) 
			if (inimigos[i].vivo)
				mover_inimigo(&inimigos[i]);

		if (bau_perto(bau1) && IsKeyPressed(KEY_E)) {
			loot_bau(bau1.conteudo, bau1.qnt, &bau1.estado);
		}

		tiro();
		
		// SEÇÃO DAS FACAS ----------------------
		for (i = 0; i < qnt_facas; i++)
			if (facas[i].ar) arremesso(&facas[i]);
		
		if (IsKeyPressed(KEY_X) && player.facas) {
			arremesso(&facas[seletor_facas]);
			player.facas--;
			seletor_facas++;
		}

		loot_faca();
		// --------------------------------------

		draw();

		/*
		for (i = 0; i < qnt_inimigos; i++) {
			if (checar_colisao(inimigos[i])) {
				double hora_morte = GetTime();

				while (GetTime() <= hora_morte + 3 && !WindowShouldClose()) morte();
			}
		}
		*/
	}


	return 0;
}
