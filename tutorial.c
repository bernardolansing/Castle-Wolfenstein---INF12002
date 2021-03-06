#include "raylib.h"
#include "main.h"

int starttutorial(void)
{
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("TUTORIAL!", 300, 20, 30, RED);
        DrawText("ARROW KEYS - MOVEMENT", 300, 60, 20, RED);
        DrawText("E - OPEN BAU", 300, 80, 20, RED);
        DrawText("E - OPEN DOOR", 300, 100, 20, RED);
        DrawText("SPACE - GUNSHOT", 300, 120, 20, RED);
        DrawText("X - THROW KNIFE", 300, 140, 20, RED);
        DrawText("P - PAUSE GAME", 300, 160, 20, RED);
        DrawText("S - SAVE GAME", 300, 180, 20, RED);
        DrawText("ESC - CLOSE", 300, 200, 20, RED);
        DrawText("Press 'R' to return !", 300, 250, 20, RED);
        if (IsKeyPressed(KEY_R)) {
            return 0;
		}

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

