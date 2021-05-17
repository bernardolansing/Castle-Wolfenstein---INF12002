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

		if ((int) GetTime() % 2) inimigo->posy += 2;
		else inimigo->posy -= 2;
	}
	else if (player.posx < inimigo->posx) {
		inimigo->posx -= 1;
		inimigo->direcao = 'E';

		if ((int) GetTime() % 2) inimigo->posy += 2;
		else inimigo->posy -= 2;
	}

	// atualiza a posição da hitbox
	inimigo->hitbox.x = inimigo->posx;
	inimigo->hitbox.y = inimigo->posy;
}

void mover() {
	int i;

	// MOVIMENTAÇÃO DO JOGADOR E DOS INIMIGOS -----------------------
	mover_jogador();
		
	for (i = 0; i < 10; i++) 
		if (inimigos[i].vivo)
			mover_inimigo(&inimigos[i]);
	// --------------------------------------------------------------

	// checar morte do jogador
	for (i = 0; i < 10; i++) {
		if (inimigos[i].vivo && checar_contato_inimigo(inimigos[i]))
			matar_jogador(i, GetTime());
	}
	
	// loot do baú
	for (i = 0; i < 10; i++) {
		if (bau_perto(baus[i]) && IsKeyPressed(KEY_E))
			loot_bau(&baus[i]);
	}

	tiro();
	
	// SEÇÃO DAS FACAS ----------------------------------------------
	for (i = 0; i < 10; i++)
		if (facas[i].ar) arremesso(&facas[i]);
	
	if (IsKeyPressed(KEY_X) && player.facas) {
		arremesso(&facas[game.seletor_facas]);
		player.facas--;
		(game.seletor_facas)++;
	}

	loot_faca();
	// --------------------------------------------------------------
	
	if (porta.liberada && porta_perto(porta))
        strcpy(game.legenda, "Voce pode passar pela porta!");
    
}
