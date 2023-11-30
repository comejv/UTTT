#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>
#include "debug.h"


#define AUDIO_FOLDER_PATH "./ASSETS/AUDIO/"
#define IMAGE_FOLDER_PATH "./ASSETS/IMAGES/"
#define FONT_FOLDER_PATH "./ASSETS/FONTS/"
#define AUDIO_FILE(name) AUDIO_FOLDER_PATH name
#define IMAGE_FILE(name) IMAGE_FOLDER_PATH name
#define FONT_FILE(name) FONT_FOLDER_PATH name

// Button state enum
typedef enum ButtonState
{
    NORMAL,
    HOVER,
    PRESSED
} ButtonState;

// Function pointer type
// typedef void (*FuncPtr)(void);

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

#endif // MAIN_H