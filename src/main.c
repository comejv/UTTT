#include "main.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void GridParameters(Rectangle *grid, int screenWidth, int screenHeight, int *PtrGridLeftOffset, int *PtrGridRightOffset, int *PtrGridUpOffset, int *PtrGridDownOffset, int *PtrGridHeight){
    *PtrGridLeftOffset = screenWidth / 10;
    *PtrGridRightOffset = screenWidth / 10;
    *PtrGridUpOffset = screenHeight / 10;
    *PtrGridDownOffset = screenHeight / 10;
    *PtrGridHeight = MIN(screenHeight - *PtrGridUpOffset - *PtrGridDownOffset, screenWidth - *PtrGridLeftOffset - *PtrGridRightOffset);
    grid->height = *PtrGridHeight;
    grid->width = *PtrGridHeight;
    grid->x = *PtrGridLeftOffset;
    grid->y = *PtrGridUpOffset;
    return;
}

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
    int gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset, gridHeight;
    Rectangle grid;
    GridParameters(&grid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset, &gridHeight);
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
        if (IsWindowResized()){
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            GridParameters(&grid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset, &gridHeight);
        }
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLinesEx(grid, 5, BLACK); 
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
    //--------------------------------------------------------------------------------------

    return 0;
}
