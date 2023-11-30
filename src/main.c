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
    int screenWidth = 800;
    int screenHeight = 450;
    float gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset;
    bool NEED_TO_DRAW = true;
    Grid mainGrid = initGrid();
    getGridGraphicParameters(mainGrid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "UTTT");
    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    Vector2 mousePoint = {0.0f, 0.0f};

    int nbButtons = 1;
    Button **buttons = (Button **)malloc(nbButtons * sizeof(Button));

    buttons[0] = CreateButton(100, 300, mainGrid->mainRectangle.x + mainGrid->mainRectangle.width, mainGrid->mainRectangle.y, "Test", NULL, NULL, RED);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();

        for (int i = 0; i < nbButtons; i++)
        {
            CheckButtonState(buttons[i], mousePoint);
        }

        if (buttons[0]->state == PRESSED)
        {
            ButtonOne(&buttons, &nbButtons);
        }
        if (nbButtons >= 2 && buttons[1]->state == PRESSED)
        {
            ButtonTwo(&buttons, &nbButtons);
        }

        // Modify screenWidth, screenHeight and Offset
        if (IsWindowResized())
        {
            NEED_TO_DRAW = true;
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            getGridGraphicParameters(mainGrid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
            for (int i = 0; i < nbButtons; i++)
            {
                buttons[i]->rect.x = mainGrid->mainRectangle.x + mainGrid->mainRectangle.width;
                buttons[i]->rect.y = mainGrid->mainRectangle.y + (buttons[i]->rect.height * i);
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
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

        BeginDrawing();
        if (1) // NEED_TO_DRAW tempfix for issue #5
        {
            NEED_TO_DRAW = false;
            ClearBackground(RAYWHITE);
            DrawMainGrid(mainGrid);

            for (int i = 0; i < nbButtons; i++)
            {
                DrawButton(buttons[i]);
            }
        }

        EndDrawing();
    }

    DEBUG_LOG("ESC or close button pressed, exiting...");

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    FreeGrid(mainGrid);
    //--------------------------------------------------------------------------------------

    return 0;
}