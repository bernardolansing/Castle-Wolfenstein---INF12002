#ifndef LERLEVEL_C
#define LERLEVEL_C

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont_inimigos = 0;
int inimigos_posx_iniciais[10];
int inimigos_posy_iniciais[10];
int player_pos_inicial[2];

void inicializador() {
	int i;

	// inicialização de afins
	game.pontuacao = 0;
	game.legenda[0] = '\0';
	game.seletor_facas = 0;
	fonte.alpha_beta = LoadFont("resources/fonts/alpha-beta.png");
	fonte.jupiter_crash = LoadFont("resources/fonts/jupyter-crash.png");
	game.executar_menu = true;

	// inicialização do jogador
	player.vidas = 3;
	player.municao = 3;
	player.facas = 2;
	player.direcao = 'E';

	// inicialização da porta
	porta.liberada = 0;

	// inicialização dos baús
	for (i = 0; i < 10; i++) {
		baus[i].estado = 0;
		baus[i].posx = 1000;
		baus[i].posy = 1000;
	}

	// inicialização dos inimigos
	for (i = 0; i < 10; i++) {
		inimigos[i].vivo = 0;
		inimigos[i].posx = 2000;
		inimigos[i].posy = 2000;
		inimigos[i].direcao = 'E';
		inimigos[i].hitbox.width = ppl_width;
		inimigos[i].hitbox.height = ppl_height;
	}

	// inicialização das facas
	for (i = 0; i < 10; i++) {
		facas[i].ar = 0;
		facas[i].hitbox.width = 29;
		facas[i].hitbox.height = 10;
		facas[i].posx = 3000;
		facas[i].posy = 3000;
	}
}

void level_reset() {
	int i;

	// reset dos baús
	for (i = 0; i < 10; i++) {
		baus[i].estado = 0;
		baus[i].posx = 1000;
		baus[i].posy = 1000;
	}

	// reset dos inimigos
	for (i = 0; i < 10; i++) {
		inimigos[i].vivo = 0;
		inimigos[i].posx = 2000;
		inimigos[i].posy = 2000;
	}

	// reset das facas
	for (i = 0; i < 10; i++) {
		facas[i].ar = 0;
		facas[i].posx = 3000;
		facas[i].posy = 3000;
	}
}

// cria o diretório do level atual
void map_loader(int level, char destino[]) {
	char diretorio[30] = "resources/levels/level";

	switch (level) {
		case 0: strcat(diretorio, "0.txt"); break;
		case 1: strcat(diretorio, "1.txt"); break;
		case 2: strcat(diretorio, "2.txt"); break;
		case 3: strcat(diretorio, "3.txt"); break;
		case 4: strcat(diretorio, "4.txt"); break;
		case 5: strcat(diretorio, "5.txt"); break;
	}

	strcpy(destino, diretorio);
}

// ler arquivo de nível
void ler_level(int level) {
	FILE *arquivo;
	char leitura, diretorio[30];
	int byte = -1, cont_baus = 0;

	map_loader(level, diretorio);
	arquivo = fopen(diretorio, "r");  // abre algum level para leitura


	while (fread(&leitura, 1, 1, arquivo)) {
		byte++;

		switch (leitura) {
			case '-': break;
			case '\n': break;

			case 'J':
			player.posx = (byte % 81) * 10;
			player.posy = (byte / 81) * 10;
			player_pos_inicial[0] = player.posx;
			player_pos_inicial[1] = player.posy;
			break;

			case 'P':
			porta.posx = (byte % 81) * 10;
			porta.posy = (byte / 81) * 10;
			break;

			case 'E':
			inimigos[cont_inimigos].posx = (byte % 81) * 10;
			inimigos[cont_inimigos].posy = (byte / 81) * 10;
			inimigos[cont_inimigos].vivo = 1;

			inimigos_posx_iniciais[cont_inimigos] = inimigos[cont_inimigos].posx;
			inimigos_posy_iniciais[cont_inimigos] = inimigos[cont_inimigos].posy;

			cont_inimigos++;
			break;

			default:
			cont_baus++;
			baus[cont_baus].posx = (byte % 81) * 10;
			baus[cont_baus].posy = (byte / 81) * 10;

			switch (leitura) {
				case 'V': baus[cont_baus].conteudo = 'V'; baus[cont_baus].qnt = 1; break;  // vida
				case 'M': baus[cont_baus].conteudo = 'M'; baus[cont_baus].qnt = 2; break;  // munição
				case 'T': baus[cont_baus].conteudo = 'P'; baus[cont_baus].qnt = 10; break;  // pontos
				case 'A': baus[cont_baus].estado = 1; break;  // aberto
			}

			break;
		}
	}

	fclose(arquivo);
}

void resetar_posicoes() {
	int i;

	for (i = 0; i < cont_inimigos; i++) {
		inimigos[i].posx = inimigos_posx_iniciais[i];
		inimigos[i].posy = inimigos_posy_iniciais[i];
	}

	player.posx = player_pos_inicial[0];
	player.posy = player_pos_inicial[1];
}

#endif
