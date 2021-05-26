#include <raylib.h>
#include "main.h"
#include "motion.c"
#include "draw.c"
#include "collision.c"
#include "string.h"
#include "lerlevel.c"
#include "salvarlevel.c"
#include "menu.c"

int main() {
	bool pause = false;
	game.level = 0;
	inicializador();

	InitWindow(largura, altura, "Castle Wolfenstein");
	InitAudioDevice();
	SetTargetFPS(60);

	// G A M E L O O P
	while (!WindowShouldClose()) {

		// execução do menu
		if (game.executar_menu) {
			switch (startmenu()) {
				
				// NOVO JOGO
				case 0:
					game.level = 0;
					level_reset();
					inicializador();
					ler_level(game.level);
					draw();
					break;

				// CARREGAR JOGO
				case 1:
					ler_level(game.level);
					carregar_save();
					draw();
					break;

				// SAIR DO JOGO
				case -1:
				return 0;
			}
		}

		game.executar_menu = false;
		
		
		// reset da legenda
		if (GetTime() - game.horalegenda > 3) memset(game.legenda, 0, 50);

		// PAUSAR E DESPAUSAR ---------------------------------------
		if (IsKeyPressed(KEY_P)) {
			pause = !pause;
			memset(game.legenda, 0, 50);
		}

		if (!pause) mover();
		else strcpy(game.legenda, "Jogo pausado!");
		// ----------------------------------------------------------

		// testar derrota
		if ((player.vidas) <= 0){
			tocar_som(sounds.defeat);
			derrota();
		}

		// salvar jogo
		if (IsKeyPressed(KEY_S)) {
			salvar_level();
			strcpy(game.legenda, "Jogo salvo!");
			game.horalegenda = GetTime();
		}

		draw();
	}

	CloseAudioDevice();
	CloseWindow();
}
