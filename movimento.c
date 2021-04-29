#include <raylib.h>
#include <main.h>

#define largura 800
#define altura 300
#define ppl_width 20
#define ppl_height 48

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
void mover_inimigo(int *posx, int *posy, char *direcao) {
	if (player.posy > *posy) {
		*posy += 1;
		*direcao = 'C';
	}
	else if (player.posy < *posy) {
		*posy -= 1;
		*direcao = 'B';
	}

	if (player.posx > *posx) {
		*posx += 1;
		*direcao = 'D';
	}
	else if (player.posx < *posx) {
		*posx -= 1;
		*direcao = 'E';
	}
}

// determina qual é o passo (1, 2, 3 ou 4) que o personagem está dando
int selec_passo(int posicao) {
	posicao %= 240;
	
	if (posicao < 61) return 0;
	if (posicao < 121) return 1;
	if (posicao < 181) return 2;
	return 3;
}





