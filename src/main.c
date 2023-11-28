#include "main.h"

int main(int argc, char **argv)
{
    extern char *optarg;
    extern int optind, opterr, optopt;

    while (getopt(argc, argv, "f:") != -1)
    {
        switch (optopt)
        {
        case 'd':
            DEBUG = 1;
            DEBUG_LOG("Debug mode enabled");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "UTTT");
    InitAudioDevice();

    SetTargetFPS(30);

    //--------------------------------------------------------------------------------------

    Vector2 mousePoint = {0.0f, 0.0f};

    Rectangle btnBounds = {275, 150, 250, 200};

    Sound click = LoadSound(AUDIO_FILE("click.wav"));

    // Load font texture with bigger size so it looks better when scaled
    Font filmNoirAventure = LoadFontEx(FONT_FILE("Film Noir Adventure.ttf"), 100, NULL, 0);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(btnBounds.x, btnBounds.y, btnBounds.width, btnBounds.height, BLUE);
        DrawTextEx(filmNoirAventure, "UTTT", (Vector2){btnBounds.x + 40, btnBounds.y + 40}, 100, 3, BLACK);

        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            DrawRectangle(btnBounds.x, btnBounds.y, btnBounds.width, btnBounds.height, RED);
            DrawTextEx(filmNoirAventure, "UTTT", (Vector2){btnBounds.x + 40, btnBounds.y + 40}, 100, 3, BLACK);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                PlaySound(click);
            }
        }

        if (DEBUG)
        {
            DrawFPS(10, 10);
        }

        EndDrawing();
    }

    DEBUG_LOG("ESC or close button pressed, exiting...");

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    UnloadSound(click);
    //--------------------------------------------------------------------------------------

    return 0;
}
