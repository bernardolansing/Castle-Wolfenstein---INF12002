#include "raylib.h"
#include "main.h"
#include "highscores.c"
#include <string.h>

#define MAX_FONTS   6

int startranking(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // InitWindow(largura, altura, "Castle of Wolfenstein");

    char aux[10];

    Font fonts[MAX_FONTS] = { 0 };

    fonts[0] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[1] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[2] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[3] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[4] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[5] = LoadFont("resources/fonts/jupiter_crash.png");

   starthighscores();

    const char *messages[MAX_FONTS] = {"Ranking",
                                vplayer[0].nome,
                                vplayer[1].nome,
                                vplayer[2].nome,
                                vplayer[3].nome,
                                vplayer[4].nome };

    const char *pontuacoes[MAX_FONTS] = {"",
                                vplayer[0].pontuacao,
                                vplayer[1].pontuacao,
                                vplayer[2].pontuacao,
                                vplayer[3].pontuacao,
                                vplayer[4].pontuacao };

    const int spacings[MAX_FONTS] = { 4, 4, 4, 4, 4, 4};

    Vector2 positions[MAX_FONTS] = { 0 };

        for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = largura/2.0f - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2.0f, (float)spacings[i]).x/2.0f;
        positions[i].y = 10.0f + fonts[i].baseSize + 35.0f*i;
    }


    Color colors[MAX_FONTS] = { RED, WHITE, WHITE, WHITE, WHITE, WHITE};


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Press 'R' to return !", 300, 250, 20, RED);
        if (IsKeyPressed(KEY_R)) {
            return;
        }
		 for (int i = 0; i < MAX_FONTS; i++)
            {
                if(i == 0){
                DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);
                }
                else
                DrawTextEx(fonts[i], TextFormat("%s %d", messages[i], pontuacoes[i]), positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);
            }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
