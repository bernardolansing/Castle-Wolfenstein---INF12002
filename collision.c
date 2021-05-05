#include <main.h>
#include <string.h>


// verifica se o inimigo colidiu com o jogador
bool checar_colisao(struct Inimigo inimigo) {
	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	Rectangle box_inimigo = {inimigo.posx, inimigo.posy, ppl_width, ppl_height};

	return (CheckCollisionRecs(box_jogador, box_inimigo));
}

// responde se h� um ba� fechado por perto
bool bau_perto(struct Bau bau) {
	if (bau.estado) return false;  // retorna false caso o ba� j� tenha sido aberto

	Rectangle box_jogador = {player.posx, player.posy, ppl_width, ppl_height};
	Rectangle box_bau = {bau.posx, bau.posy, 65, 65};

	return (CheckCollisionRecs(box_jogador, box_bau));
}

// marca o ba� como fechado e d� ao jogador seus esp�lios
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

	// d� 50 pontos por ter aberto o ba�
	game.pontuacao += 50;
}

Rectangle disparobox() {
	Rectangle box_bullet;

	switch (player.direcao) {
		case 'C': box_bullet.x = player.posx; box_bullet.y = player.posy / 2;
		box_bullet.width = 1; box_bullet.height = player.posy;
		break;

		case 'B': box_bullet.x = player.posx; box_bullet.y = (player.posy + altura) / 2;
		box_bullet.width = 1; box_bullet.height = altura - player.posy;
		break;

		case 'D': box_bullet.x = (largura + player.posx) / 2; box_bullet.y = player.posy - 24;
		box_bullet.width = largura - player.posx; box_bullet.height = 1;
		break;

		case 'E': box_bullet.x = (largura - player.posx) / 2; box_bullet.y = player.posy;
		box_bullet.width = largura - player.posx; box_bullet.height = 1;
		break;
	}

	DrawRectangle(box_bullet.x, box_bullet.y, box_bullet.width, box_bullet.height, GREEN);
	
	return box_bullet;
}

void tiro() {
	int i;
	// Rectangle box_inimigo;

	if (IsKeyPressed(KEY_SPACE)) {
		
		for (i = 0; i < qnt_inimigos; i++) {
			Rectangle box_inimigo = {inimigos[i].posx, inimigos[i].posy, ppl_width, ppl_height};
			if (CheckCollisionRecs(disparobox(), box_inimigo)) inimigos[i].vivo = 0;
		}
	}
}

