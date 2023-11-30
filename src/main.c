#include "main.h"

/*
AddButton : add a button to an array of buttons
Parameters:
    Button *buttons
    float height
    float width
    float posX
    float posY
    Texture2D texture : if texture are defined, ignore colors
    Texture2D textureHover : optional
    Color col : used if no texture is defined
    Color colHover : optional
*/
void AddButton(Button *buttons, float buttonHeight, float buttonWidth, float posX, float posY, const char *texturePath, const char *textureHoverPath, Color col, Color colHover)
{
    Button newButton;
    Rectangle rectPos;

    rectPos.height = buttonHeight;
    rectPos.width = buttonWidth;
    rectPos.x = posX;
    rectPos.y = posY;

    newButton.rect = rectPos;

    if (texturePath != NULL)
    {
        newButton.img = LoadTexture(texturePath);
        if (textureHoverPath != NULL)
        {
            newButton.hoverImg = LoadTexture(textureHoverPath);
        }
    }
    else
    {
        newButton.col = col;
        newButton.hoverCol = colHover;
    }
}

/*
GridParameters : A function to get parameters for the main grid depending of screenWidth and screenHeight
Parameters :
    Rectangle *grid : A pointer to the rectangle representating the main grid which will be modified
    int screenWidth : current screen width
    int screenHeight :  current screen height
    int *PtrGridLeftOffset : pointer to gridLeftOffset which will be modified
    int *PtrGridLeftOffset : pointer to gridRightOffset which will be modified
    int *PtrGridLeftOffset : pointer to gridUpOffset which will be modified
    int *PtrGridLeftOffset : pointer to gridDownOffset which will be modified
Return : None
Side effect :
    grid, gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset get modified
*/
void GridParameters(Rectangle *grid, int screenWidth, int screenHeight, int *PtrGridLeftOffset, int *PtrGridRightOffset, int *PtrGridUpOffset, int *PtrGridDownOffset)
{
    *PtrGridLeftOffset = screenWidth / 10;
    *PtrGridRightOffset = screenWidth / 10;
    *PtrGridUpOffset = screenHeight / 10;
    *PtrGridDownOffset = screenHeight / 10;
    int gridHeight = MIN(screenHeight - *PtrGridUpOffset - *PtrGridDownOffset, screenWidth - *PtrGridLeftOffset - *PtrGridRightOffset);
    grid->height = gridHeight;
    grid->width = gridHeight;
    grid->x = *PtrGridLeftOffset;
    grid->y = *PtrGridUpOffset;
    return;
}

/*
SubGridParameters : A function to get parameters for a 3*3 sub grid based on it's container
Parameters :
    Rectangle *subgrid : A pointer to the rectangle representating the sub grid which will be modified
    Rectangle grid : the container's grid
    int i,j : coordonates of the subgrid in the main one
Return : None
Side effect :
    subgrid get modified
*/
void SubGridParameters(Rectangle *subgrid, Rectangle grid, int i, int j)
{
    subgrid->height = grid.height / 3;
    subgrid->width = grid.width / 3;
    subgrid->x = grid.x + ((grid.width / 3) * i);
    subgrid->y = grid.y + ((grid.height / 3) * j);
    return;
}

/*
DrawMainGrid : A function to draw the main grid and it's tiles depending of an initial rectangle
Parameters : Rectangle grid, the main rectangle that contain the grid
Return : None
Side effect : Draw the grid in the main window using SubGridParameters
*/
void DrawMainGrid(Rectangle grid)
{
    Rectangle subgrid;
    Rectangle tile;
    // Building the initial grid
    DrawRectangleLinesEx(grid, 8, BLACK);
    // Draw the others grid based on the initial one
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            SubGridParameters(&subgrid, grid, i, j);
            DrawRectangleLinesEx(subgrid, 5, BLACK);
            // Draw tiles in the subgrid
            for (int tile_i = 0; tile_i < 3; tile_i++)
            {
                for (int tile_j = 0; tile_j < 3; tile_j++)
                {
                    SubGridParameters(&tile, subgrid, tile_i, tile_j);
                    DrawRectangleLinesEx(tile, 1, BLACK);
                }
            }
        }
    }
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
    int gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset;
    bool NEED_TO_DRAW = true;
    Rectangle grid;
    GridParameters(&grid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
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
            GridParameters(&grid, screenWidth, screenHeight, &gridLeftOffset, &gridRightOffset, &gridUpOffset, &gridDownOffset);
        }
        BeginDrawing();
        mousePoint = GetMousePosition();
        if (NEED_TO_DRAW)
        {
            NEED_TO_DRAW = false;
            ClearBackground(RAYWHITE);
            DrawMainGrid(grid);
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
