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

typedef enum
{
    NORMAL,
    HOVER,
    PRESSED
} ButtonState;

typedef struct
{
    Rectangle rect;
    char *text;
    Texture2D img;
    Texture2D imgHover;
    Color col;
    Color colHover;
    ButtonState state;
} Button;

#endif // MAIN_H