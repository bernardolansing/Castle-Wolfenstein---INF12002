#include <raylib.h>
#include <main.h>
#include <motion.c>
#include <draw.c>
#include <collision.c>
#include <string.h>
#include <lerlevel.c>


int main() {
	int seletor_facas = 0;
	bool pause = false;

	inicializador();
	ler_level();

	InitWindow(largura, altura, "Castle Wolfenstein");
	SetTargetFPS(60);

	// G A M E L O O P
	while (!WindowShouldClose()) {

		// reset da legenda
		if (GetTime() - game.horalegenda > 3) memset(game.legenda, 0, 50);

//		DrawText(FormatText("%i", GetFPS()), 400, 10, 16, WHITE);		
		
		// pausar e despausar
		if (IsKeyPressed(KEY_P)) {pause = !pause; memset(game.legenda, 0, 50);}

		if (!pause) mover(&seletor_facas);
		else strcpy(game.legenda, "Jogo pausado!");

		draw();
	}


	return 0;
}
