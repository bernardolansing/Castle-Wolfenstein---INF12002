#include "raylib.h"
#include "main.h"
#define MAX_FONTS 4

int startcredits(void)
{
          Font fonts[MAX_FONTS] = { 0 };

    fonts[0] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[1] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[2] = LoadFont("resources/fonts/jupiter_crash.png");
    fonts[3] = LoadFont("resources/fonts/jupiter_crash.png");

    const char *messages[MAX_FONTS] = {"Credits",
                                "Bernardo Lansing",
                                "Frederico Villani",
                                "UFRGS 2020/2"};

    const int spacings[MAX_FONTS] = { 4, 4, 4, 4};

    Vector2 positions[MAX_FONTS] = { 0 };

    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = largura/2.0f - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2.0f, (float)spacings[i]).x/2.0f;
        positions[i].y = 10.0f + fonts[i].baseSize + 50.0f*i;
    }

    Color colors[MAX_FONTS] = { RED, WHITE, WHITE, RED};

    int colorState[MAX_FONTS] = { 0 };
    // Initialization
    //--------------------------------------------------------------------------------------
  //  InitWindow(largura, altura, "Castle of Wolfenstein");

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

        for (int i = 0; i < MAX_FONTS; i++)
            {
                DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);
            }
        DrawText("Press 'R' to return!", 300, 250, 20, RED);
        if (IsKeyPressed(KEY_R)) {
            return;
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
