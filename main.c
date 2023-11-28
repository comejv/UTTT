#include <raylib.h>

#define AUDIO_FOLDER_PATH "./ASSETS/AUDIO/"
#define IMAGE_FOLDER_PATH "./ASSETS/IMAGES/"
#define FONT_FOLDER_PATH "./ASSETS/FONTS/"
#define AUDIO_FILE(name) AUDIO_FOLDER_PATH name
#define IMAGE_FILE(name) IMAGE_FOLDER_PATH name
#define FONT_FILE(name) FONT_FOLDER_PATH name

int main()
{
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

    Font filmNoirAventure = LoadFont(FONT_FILE("Film Noir Adventure.ttf"));

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

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    UnloadSound(click);
    //--------------------------------------------------------------------------------------

    return 0;
}
