#include <main.h>
#include <string.h>


// verifica se o inimigo colidiu com o jogador
bool checar_colisao(struct Inimigo inimigo) {
	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};

	return (CheckCollisionRecs(box_jogador, inimigo.hitbox));
}

// responde se h� um ba� fechado por perto
bool bau_perto(struct Bau bau) {
	if (bau.estado) return false;  // retorna false caso o ba� j� tenha sido aberto

	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	Rectangle box_bau = {bau.posx, bau.posy, 65, 65};

	return (CheckCollisionRecs(box_jogador, box_bau));
}

// marca o baú como fechado e dá ao jogador seus espólios
void loot_bau(char conteudo, int qnt, int *fechadura) {
	*fechadura = 1;  // define o ba� como aberto (bau.estado = 1)

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
}

void loot_faca() {	
	int i;
	Rectangle box_faca;
	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	box_faca.width = 35;
	box_faca.height = 30;

	for (i = 0; i < qnt_facas; i++) {
		if (!facas[i].ar) {
			box_faca.x = facas[i].posx - 17;
			box_faca.y = facas[i].posy;
			//DrawRectangleLines(box_faca.x, box_faca.y, box_faca.width, box_faca.height, BLUE);
			//DrawRectangleLines(box_jogador.x, box_jogador.y, box_jogador.width, box_jogador.height, BLUE);

			if (CheckCollisionRecs(box_jogador, box_faca)) {
				facas[i].posx = largura * 2;
				facas[i].posy = altura * 2;
				player.facas++;
				strcpy(game.legenda, "Voce apanhou uma faca!");
				game.horalegenda = GetTime();
			}
		}
	}
}

Rectangle disparobox() {
	Rectangle box_bullet;

	switch (player.direcao) {
		case 'C': box_bullet.x = player.posx + 17; box_bullet.y = 0;
		box_bullet.width = 1; box_bullet.height = player.posy;
		break;

		case 'B': box_bullet.x = player.posx + 17; box_bullet.y = player.posy;
		box_bullet.width = 1; box_bullet.height = altura - player.posy;
		break;

		case 'D': box_bullet.x = player.posx + 11; box_bullet.y = player.posy + 24;
		box_bullet.width = largura; box_bullet.height = 1;
		break;

		case 'E': box_bullet.x = 0; box_bullet.y = player.posy + 24;
		box_bullet.width = player.posx + 17; box_bullet.height = 1;
		break;
	}
	
	return box_bullet;
}

void matar_inimigo(struct Inimigo *inimigo) {
	inimigo->vivo = 0;
	inimigo->horamorte = GetTime();
	strcpy(game.legenda, "Voce abateu um inimigo!");
	game.horalegenda = GetTime();
	game.pontuacao += 10;
}

void tiro() {
	int i;

	if (IsKeyPressed(KEY_SPACE) && player.municao) {
		
		for (i = 0; i < qnt_inimigos; i++) {
			Rectangle box_inimigo = {inimigos[i].posx, inimigos[i].posy, ppl_width, ppl_height};
			if (CheckCollisionRecs(disparobox(), box_inimigo) && inimigos[i].vivo)
				matar_inimigo(&inimigos[i]);
		}

		player.horadisparo = GetTime();
		player.municao--;
	}
}

int hitfaca(struct Faca faca) {
	int i;

	// testar se a faca acerta algum inimigo
	for (i = 0; i < qnt_inimigos; i++) {
		if (CheckCollisionRecs(faca.hitbox, inimigos[i].hitbox)) {
			matar_inimigo(&inimigos[i]);
			return 1;
		}
	}

	// testar se a faca acerta alguma parede
	if (faca.posx < 15 || faca.posx > largura - 15) return 1;
	if (faca.posy < 15 || faca.posy > altura - 15 - hud_height) return 1;

	return 0;
}

void arremesso(struct Faca *faca) {
	// caso a faca esteja guardada, será arremessada agora
	if (!faca->ar) {
		faca->posx = player.posx;
		faca->posy = player.posy;
		faca->hitbox.x = player.posx;
		faca->hitbox.y = player.posy;
		faca->direcao = player.direcao;
	}

	// tendo sido arremessada, percorrerá o cenário de acordo com a direção	
	faca->ar = 1;

	switch (faca->direcao) {
		case 'C': faca->posy -= 3; faca->hitbox.y -= 3; break;
		case 'B': faca->posy += 3; faca->hitbox.y += 3; break;
		case 'D': faca->posx += 3; faca->hitbox.x += 3; break;
		case 'E': faca->posx -= 3; faca->hitbox.x -= 3; break;
	}

	// checa a colisão da faca
	if (hitfaca(*faca)) {
		faca->ar = 0;
		faca->drop.x = faca->posx;
		faca->drop.y = faca->posy;
	}
}

