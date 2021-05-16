#include <main.h>
#include <stdio.h>
#include <stdlib.h>

void inicializador() {
	int i;

	// inicialização de afins
	game.pontuacao = 0;
	game.legenda[0] = '\0';
	game.seletor_facas = 0;
	fonte.alpha_beta = LoadFont("resources/fonts/alpha-beta.png");
	fonte.jupiter_crash = LoadFont("resources/fonts/jupyter-crash.png");
	
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


// ler arquivo de nível
void ler_level() {
	FILE *arquivo;
	char leitura;
	int byte = -1, cont_inimigos = 0, cont_baus = 0;

	arquivo = fopen("resources/levels/level0.txt", "rt");  // abre algum level para leitura

	while (fread(&leitura, 1, 1, arquivo)) {
		byte++;
		
		switch (leitura) {
			case '-': break;
			case '\n': break;

			case 'J': 
			player.posx = (byte % 81) * 10;
			player.posy = (byte / 81) * 10;
			break;

			case 'P':
			porta.posx = (byte % 81) * 10;
			porta.posy = (byte / 81) * 10;
			break;

			case 'E':
			inimigos[cont_inimigos].posx = (byte % 81) * 10;
			inimigos[cont_inimigos].posy = (byte / 81) * 10;
			inimigos[cont_inimigos].vivo = 1;
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
	