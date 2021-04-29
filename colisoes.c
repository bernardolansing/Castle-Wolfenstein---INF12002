#include <raylib.h>
#include <colisoes.h>


#define ppl_width 20
#define ppl_height 48

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