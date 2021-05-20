#ifndef SALVARLEVEL_C
#define SALVARLEVEL_C


#include "main.h"
#include <stdio.h>

void salvar_level() {
	FILE *arquivo = fopen("savegame.txt", "w");
	int i;

	// gravar o level
	fprintf(arquivo, "%i\n", game.level);

	// gravar a posição e stats do jogador
	fprintf(arquivo, "%i %i\n", player.posx, player.posy);
	fprintf(arquivo, "%i %i %i\n", player.municao, player.facas, player.vidas);

	// gravar a posição dos inimigos
	for (i = 0; i < 10; i++)
		fprintf(arquivo, "%i %i %i\n", inimigos[i].vivo, inimigos[i].posx, inimigos[i].posy);

	// gravar o estado dos baús
	for (i = 0; i < 10; i++)
		fprintf(arquivo, "%i\n", baus[i].estado);

	// gravar as informações das facas
	for (i = 0; i < 10; i++)
		fprintf(arquivo, "%c %i %i %i\n", facas[i].direcao, facas[i].ar, facas[i].posx, facas[i].posy);

	// gravar dados da partida
	fprintf(arquivo, "%i %i\n", game.pontuacao, game.seletor_facas);



	fclose(arquivo);
}


void carregar_save() {
	FILE *arquivo = fopen("savegame.txt", "r");
	int i;

	// level
	fscanf(arquivo, "%i", &game.level);

	// player
	fscanf(arquivo, "%i %i", &player.posx, &player.posy);
	fscanf(arquivo, "%i %i %i", &player.municao, &player.facas, &player.vidas);


	// inimigos
	for (i = 0; i < 10; i++)
		fscanf(arquivo, "%i %i %i", &inimigos[i].vivo, &inimigos[i].posx, &inimigos[i].posy);


	// baús
	for (i = 0; i < 10; i++)
		fscanf(arquivo, "%i", &baus[i].estado);

	// facas
	for (i = 0; i < 10; i++)
		fscanf(arquivo, "%c %i %i %i\n", &facas[i].direcao, &facas[i].ar, &facas[i].posx, &facas[i].posy);

	fscanf(arquivo, "%i %i", &game.pontuacao, &game.seletor_facas);

	fclose(arquivo);
}

#endif
