#ifndef CREDITS_C
#define CREDITS_C

#include "raylib.h"
#include "main.h"
#define C_MAX_FONTS 4

int startcredits(void)
{
	Font fonts[C_MAX_FONTS] = { 0 };

	fonts[0] = LoadFont("resources/fonts/jupiter_crash.png");
	fonts[1] = LoadFont("resources/fonts/jupiter_crash.png");
	fonts[2] = LoadFont("resources/fonts/jupiter_crash.png");
	fonts[3] = LoadFont("resources/fonts/jupiter_crash.png");

	const char *messages[C_MAX_FONTS] = {"Credits",
								"Bernardo Lansing",
								"Frederico Villani",
								"UFRGS 2020/2"};

	const int spacings[C_MAX_FONTS] = { 4, 4, 4, 4};

	Vector2 positions[C_MAX_FONTS] = { 0 };

	for (int i = 0; i < C_MAX_FONTS; i++)
	{
		positions[i].x = largura/2.0f - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2.0f, (float)spacings[i]).x/2.0f;
		positions[i].y = 10.0f + fonts[i].baseSize + 50.0f*i;
	}

	Color colors[C_MAX_FONTS] = { RED, WHITE, WHITE, RED};

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < C_MAX_FONTS; i++)
			DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);

		DrawText("Press 'R' to return!", 300, 250, 20, RED);

		if (IsKeyPressed(KEY_R)) {
			return 0;
		}

		EndDrawing();

	}

	CloseWindow();
	return 0;
}

#endif
