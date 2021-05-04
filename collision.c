#include <raylib.h>
#include <string.h>
#include "main.h"

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

