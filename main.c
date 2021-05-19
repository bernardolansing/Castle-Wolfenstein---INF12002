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
	ler_level(game.level);




	//carregar_save();

	InitWindow(largura, altura, "Castle Wolfenstein");
    InitAudioDevice();

    Sound death = LoadSound("resources/sound/death.mp3");

    Sound defeat = LoadSound("resources/sound/defeat.mp3");

    Sound yell = LoadSound("resources/sound/yell.mp3");

    Sound shot = LoadSound("resources/sound/shot.mp3");

    Sound knife = LoadSound("resources/sound/knife.mp3");

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
		if ((player.vidas) <= 0){
            PlaySound(defeat);
            derrota();
            PlaySound(death);
            PlaySound(shot);
            PlaySound(knife);
            PlaySound(yell);
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
