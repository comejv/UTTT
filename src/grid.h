#ifndef __GRID_H__
#define __GRID_H__
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Grid_t {
    Rectangle mainRectangle;
    Rectangle *tiles;
    int **data;
} Grid_t; 

typedef struct Grid_t *Grid;


/*
initGrid : A function to initialize a grid
Parameters : None
Return : An empty grid 
Side-effect : None 
*/
Grid initGrid();


/*
GridParameters : A function to calcul grid parameters based on window width and height
Parameters : 
    Grid g : The grid that will be modified
    int screenWidth : current screen width
    int screenHeight :  current screen height
    int *PtrGridLeftOffset : pointer to gridLeftOffset which will be modified 
    int *PtrGridLeftOffset : pointer to gridRightOffset which will be modified 
    int *PtrGridLeftOffset : pointer to gridUpOffset which will be modified 
    int *PtrGridLeftOffset : pointer to gridDownOffset which will be modified 
Return : None 
Side effect :
    g, gridLeftOffset, gridRightOffset, gridUpOffset, gridDownOffset get modified 
*/
void getGridGraphicParameters(Grid g, int screenWidth, int screenHeight, float *PtrGridLeftOffset, float *PtrGridRightOffset, float *PtrGridUpOffset, float *PtrGridDownOffset);


/*
DrawMainGrid : A function to draw the main grid and it's tiles 
Parameters : Grid mainGrid, the main grid
Return : None 
Side effect : Draw the grid in the main window using SubGridParameters
*/
void DrawMainGrid(Grid mainGrid);

/*
FreeGrid : A function to free memory from grid
Parameters : Grid g
Return : None 
Side effect : Free g memory 
*/
void FreeGrid(Grid g);
#endif