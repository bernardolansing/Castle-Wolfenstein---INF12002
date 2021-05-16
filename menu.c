#include "raylib.h"
#include "main.h"

#define MAX_FONTS   6

int main(void)
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
                                "Creditos",
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
                    if (!(IsMouseButtonPressed(MOUSE_CURSOR_IBEAM)))
                    {
                    DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    }
                    if(IsMouseButtonPressed(MOUSE_CURSOR_IBEAM)){
                    switch (i){
                        case 0:
                    //jogo();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    break;
                case 1:
                    //carrega_jogo();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    break;
                case 2:
                    //tutorial();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    break;
                case 3:
                    //ranking();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    break;
                case 4:
                    //creditos();
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    break;
                case 5:
                    DrawTextEx(fonts[i], "CLICOU", positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], MAROON);
                    return;
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

    return 0;
}
