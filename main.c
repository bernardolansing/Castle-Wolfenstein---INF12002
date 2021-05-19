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
  //ler_level(game.level);




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
		if (game.executar_menu) {
			switch (startmenu()){
				case 0:
					//inicializador();
					ler_level(game.level);
					draw();
					break;
				case 1:
					//inicializador();
					ler_level(game.level);
					carregar_save();
					draw();
					break;

				case -1:
				return 0;
        	}
        }
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
		}

		// som inimigo morto
		if(som_yell == 1){
            PlaySound(yell);
            som_yell = 0;
		}

        // som inimigo morto
		if(som_death == 1){
            PlaySound(death);
            som_death = 0;
		}

        // som tiro
		if(som_shot == 1){
            PlaySound(shot);
            som_shot = 0;
		}

        // som hit faca
		if(som_knife == 1){
            PlaySound(knife);
            som_knife = 0;
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
