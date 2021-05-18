#ifndef MENU_C
#define MENU_C

#include "raylib.h"
#include "main.h"
#include "ranking.c"
#include "credits.c"
#include "tutorial.c"

#define MAX_FONTS   6

void startmenu(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(largura, altura, "Castle of Wolfenstein");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Font fonts[MAX_FONTS] = { 0 };

    fonts[0] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[1] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[2] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[3] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[4] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[5] = LoadFont("resources/fonts/jupiter_crash.png");

    const char *messages[MAX_FONTS] = {"New Game",
                                "Load Game",
                                "Tutorial",
                                "Ranking",
                                "Credits",
                                "Quit" };

    const int spacings[MAX_FONTS] = { 4, 4, 4, 4, 4, 4};

    Vector2 positions[MAX_FONTS] = { 0 };

    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = largura/2.0f - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2.0f, (float)spacings[i]).x/2.0f;
        positions[i].y = 45.0f + fonts[i].baseSize + 35.0f*i;
    }

    Color colors[MAX_FONTS] = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};

    int colorState[MAX_FONTS] = { 0 };

    Rectangle colorsRecs[MAX_FONTS] = { 0 };     // Rectangles array

    for (int i = 0; i < MAX_FONTS; i++)
    {
        colorsRecs[i].x = 300.0f;
        colorsRecs[i].y = 60.0f + 35.0f *i;
        colorsRecs[i].width = 200.0f;
        colorsRecs[i].height = 38.0f;
    }


    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();

        for (int i = 0; i < MAX_FONTS; i++)
        {
            if (CheckCollisionPointRec(mousePoint, colorsRecs[i])) colorState[i] = 1;
            else colorState[i] = 0;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

           DrawText("Castle of Wolfeinstein", 170, 20, 45, RED);

            for (int i = 0; i < MAX_FONTS; i++)
            {
                DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);

                    if(colorState[i]){
                    if (!(IsMouseButtonPressed(0)))
                    {
                    DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    }
                    if(IsMouseButtonPressed(0)){
                    switch (i){
                        case 0:
                        acessos++;
                        return;
                    break;
                case 1:
                    //if(verifica_jogo() == 1){}
                   // carregar_save();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    //else{}
                    break;
                case 2:
                    starttutorial();
                    break;
                case 3:
                    startranking();
                    break;
                case 4:
                    startcredits();
                    break;
                case 5:
                    CloseWindow();
                    }
                }
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (int i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);

    CloseWindow();                 // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return;
}

#endif

