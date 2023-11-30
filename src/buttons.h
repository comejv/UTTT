#ifndef BUTTONS_H
#define BUTTONS_H

#include <raylib.h>
#include <stdlib.h>
#include "debug.h"
#include "macros.h"

// Button state enum
typedef enum ButtonState
{
    NORMAL,
    HOVER,
    PRESSED
} ButtonState;

// Button struct
typedef struct
{
    Rectangle rect;
    char *text;
    bool useTexture;
    Texture2D texture;
    Texture2D textureHover;
    Texture2D texturePressed;
    Color col;
    ButtonState state;
} Button;

/*
ChangeColorBrightness : change the brightness of a color
Parameters:
    Color color : the color to change
    float brightness : the brightness to add
*/
Color ChangeColorBrightness(Color color, float brightness);

/*
AddButton : add a button to an array of buttons
Parameters:
    float height
    float width
    float posX
    float posY
    Texture2D texture : if texture are defined, ignore colors
    Texture2D textureHover : optional
    Color col : used if no texture is defined. Will be darkened when hovered
*/
Button *CreateButton(float buttonHeight, float buttonWidth, float posX, float posY, char *text, const char *texturePath, const char *textureHoverPath, Color col);

/*
CheckButtonState : check if the mouse is hovering or clicking on a button
Parameters:
    Button *button : the button to check
    Vector2 mousePoint : the mouse position
*/
void CheckButtonState(Button *button, Vector2 mousePoint);

/*
DrawButton : draw a button
Parameters:
    Button *button : the button to draw
*/
void DrawButton(Button *button);

/*
ButtonOne : test function, action for button one
Parameters:
    Button ***buttons : pointer to the array of buttons
    int *nbButtons : pointer to the number of buttons
*/
void ButtonOne(Button ***buttons, int *nbButtons);

/*
ButtonTwo : test function, action for button two
Parameters:
    Button ***buttons : pointer to the array of buttons
    int *nbButtons : pointer to the number of buttons
*/
void ButtonTwo(Button ***buttons, int *nbButtons);

#endif // BUTTONS_H