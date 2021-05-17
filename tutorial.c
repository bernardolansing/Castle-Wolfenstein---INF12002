#include "raylib.h"
#include "main.h"

int starttutorial(void)
{
    // Initialization
    //-------------------------------------------------------------------------------------

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

        DrawText("TUTORIAL!", 190, 200, 20, RED);
        DrawText("Press 'R' to return !", 300, 250, 20, RED);
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

