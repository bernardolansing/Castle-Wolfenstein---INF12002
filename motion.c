#include <raylib.h>
#include <string.h>
#include <main.h>
#include <collision.c>

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
void mover_inimigo(struct Inimigo *inimigo) {
	if (player.posy > inimigo->posy) {
		inimigo->posy += 1;
		inimigo->direcao = 'C';
	}
	else if (player.posy < inimigo->posy) {
		inimigo->posy -= 1;
		inimigo->direcao = 'B';
	}

	if (player.posx > inimigo->posx) {
		inimigo->posx += 1;
		inimigo->direcao = 'D';
	}
	else if (player.posx < inimigo->posx) {
		inimigo->posx -= 1;
		inimigo->direcao = 'E';
	}

	// atualiza a posição da hitbox
	inimigo->hitbox.x = inimigo->posx;
	inimigo->hitbox.y = inimigo->posy;
}

void mover(int *seletor_facas) {
	int i;

	// MOVIMENTAÇÃO DO JOGADOR E DOS INIMIGOS -----------------------
	mover_jogador();
		
	for (i = 0; i < qnt_inimigos; i++) 
		if (inimigos[i].vivo)
			mover_inimigo(&inimigos[i]);
	// --------------------------------------------------------------

	if (bau_perto(bau1) && IsKeyPressed(KEY_E)) {
		loot_bau(bau1.conteudo, bau1.qnt, &bau1.estado);
	}

	tiro();
	
	// SEÇÃO DAS FACAS ----------------------------------------------
	for (i = 0; i < qnt_facas; i++)
		if (facas[i].ar) arremesso(&facas[i]);
	
	if (IsKeyPressed(KEY_X) && player.facas) {
		arremesso(&facas[*seletor_facas]);
		player.facas--;
		(*seletor_facas)++;
	}

	loot_faca();
	// --------------------------------------------------------------
}
