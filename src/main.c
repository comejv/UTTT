#include "main.h"
#include "grid.h"

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
    int screenWidth = 800;
    int screenHeight = 450;
    float gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset;
    bool NEED_TO_DRAW = true;
    Grid mainGrid = initGrid();
    getGridGraphicParameters(mainGrid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "UTTT");
    InitAudioDevice();
    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    Vector2 mousePoint = {0.0f, 0.0f};

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Modify screenWidth, screenHeight and Offset
        if (IsWindowResized())
        {
            NEED_TO_DRAW = true;
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            getGridGraphicParameters(mainGrid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
        }
        BeginDrawing();
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            mousePoint = GetMousePosition();
            int x = (mousePoint.x - mainGrid->mainRectangle.x) / (mainGrid->mainRectangle.height / 9);
            int y = (mousePoint.y - mainGrid->mainRectangle.y) / (mainGrid->mainRectangle.height / 9);
            if (x < 0 || x >= 9 || y < 0 || y >= 9)
            {
                x = -1;
                y = -1;
            }
            char *text = malloc(sizeof(char) * 10);
            sprintf(text, "%d %d", x, y);
            INFO_LOG("Player clicked on : %d %d position", x, y);
        }
        if (NEED_TO_DRAW)
        {
            NEED_TO_DRAW = false;
            ClearBackground(RAYWHITE);
            DrawMainGrid(mainGrid);
        }
        EndDrawing();
    }

    DEBUG_LOG("ESC or close button pressed, exiting...");

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    FreeGrid(mainGrid);
    //--------------------------------------------------------------------------------------

    return 0;
}
