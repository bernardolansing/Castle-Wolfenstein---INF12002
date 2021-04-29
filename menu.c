#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

int menu(void)
{
    const int screenWidth = 800;
    const int screenHeight = 300;

    InitWindow(screenWidth, screenHeight, "Castle Wolfstein");

    font = LoadFont("resources/fonts/jupiter_crash.png");
      const char *messages[MAX_FONTS] = {"New Game",
                                "Load Game",
                                "Tutorial",
                                "Ranking",
                                "Quit"};

    const int spacings = 4;

    Vector2 positions[MAX_FONTS] = { 0 };

    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = screenWidth/2.0f - MeasureTextEx(font, messages[i], fonts[i].baseSize*2.0f, (float)spacings).x/2.0f;
        positions[i].y = 80.0f + fonts[i].baseSize + 35.0f*i;
    }


    Color colors[MAX_FONTS] = { WHITE, WHITE , WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

       DrawText("Castle of Wolfstein", 200, 30, 45, RED);

        for (int i = 0; i < MAX_FONTS; i++)
        {
            DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);
        }

     /*   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (!collision)
            {
                ray = GetMouseRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = CheckCollisionRayBox(ray,
                            (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2 },
                                          (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2 }});
            }
            else collision = false;
        }*/
        EndDrawing();
    }


    for (int i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);

    CloseWindow();

    return 0;
}


int main()
{
    menu();

}
