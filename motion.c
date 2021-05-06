#include <raylib.h>
#include <string.h>
#include <main.h>

// movimenta o jogador pelo cen�rio
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
