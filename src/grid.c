#include "grid.h"
#include <raylib.h>


Grid initGrid(){
    Grid g = (Grid)malloc(sizeof(Grid_t));
    g->tiles = (Rectangle *)malloc(sizeof(Rectangle) * 9);
    g->data = (int **)malloc(sizeof(int *) * 9);
    for (int i = 0; i < 9; i++)
    {
        g->data[i] = (int *)malloc(sizeof(int) * 9);
    }
    return g;
}


void getGridGraphicParameters(Grid g, int screenWidth, int screenHeight, float *PtrGridLeftOffset, float *PtrGridRightOffset, float *PtrGridUpOffset, float *PtrGridDownOffset)
{
    *PtrGridLeftOffset = screenWidth / 10;
    *PtrGridRightOffset = screenWidth / 10;
    *PtrGridUpOffset = screenHeight / 10;
    *PtrGridDownOffset = screenHeight / 10;
    int gridHeight = MIN(screenHeight - *PtrGridUpOffset - *PtrGridDownOffset, screenWidth - *PtrGridLeftOffset - *PtrGridRightOffset);
    g->mainRectangle.height = gridHeight;
    g->mainRectangle.width = gridHeight;
    g->mainRectangle.x = *PtrGridLeftOffset;
    g->mainRectangle.y = *PtrGridUpOffset;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            g->tiles[(i*3)+j].height = g->mainRectangle.height / 3;
            g->tiles[(i*3)+j].width = g->mainRectangle.width / 3;
            g->tiles[(i*3)+j].x = g->mainRectangle.x + ((g->mainRectangle.width / 3) * i);
            g->tiles[(i*3)+j].y = g->mainRectangle.y + ((g->mainRectangle.height / 3) * j);
        }
    }
    return;
}

void DrawMainGrid(Grid mainGrid)
{
    Rectangle tile, subGrid;
    // Building the initial grid
    DrawRectangleLinesEx(mainGrid->mainRectangle, 8, BLACK);
    // Draw the sub grid
    for (int k = 0; k < 9; k++){
        subGrid = mainGrid->tiles[k];
        DrawRectangleLinesEx(subGrid, 5, BLACK);
        // Draw the tiles 
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tile.height = subGrid.height / 3;
                tile.width = subGrid.width / 3;
                tile.x = subGrid.x + ((subGrid.width / 3) * i);
                tile.y = subGrid.y + ((subGrid.height / 3) * j);
                DrawRectangleLinesEx(tile, 1, BLACK);
            }
        }
    }
}


void FreeGrid(Grid g){
    if (g){
        for (int i = 0; i < 9; i++){
            free(g->data[i]);
        }
        free(g->data);
        free(g->tiles);
    }
    free(g);
}