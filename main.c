#include <raylib.h>
#include "main.h"
#include "motion.c"
#include "draw.c"
#include "collision.c"
#include "string.h"
#include "lerlevel.c"
#include "salvarlevel.c"
#include "menu.c"

int i = 0;



int main() {
	bool pause = false;
	
	game.level = 0;
    inicializador();
	ler_level(game.level);

	//carregar_save();

	InitWindow(largura, altura, "Castle Wolfenstein");
	SetTargetFPS(60);

	// G A M E L O O P
	while (!WindowShouldClose()) {

		// execução do menu
		if (game.executar_menu) startmenu();
		game.executar_menu = false;

		// reset da legenda
		if (GetTime() - game.horalegenda > 3) memset(game.legenda, 0, 50);

		// pausar e despausar
		if (IsKeyPressed(KEY_P)) {
			pause = !pause;
			memset(game.legenda, 0, 50);
		}

		if (!pause) mover();
		else strcpy(game.legenda, "Jogo pausado!");

		// testar derrota
		if (!player.vidas && ( i == 0)){
            derrota();
            i++;
		}

		// salvar jogo
		if (IsKeyPressed(KEY_S)) {
			salvar_level();
			strcpy(game.legenda, "Jogo salvo!");
			game.horalegenda = GetTime();
		}

		draw();
	}

	return 0;
}
