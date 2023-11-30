#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>
#include "debug.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
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
    Texture2D img;
    Texture2D hoverImg;
    Color col;
    Color hoverCol;
    ButtonState state;
} Button;

#endif // MAIN_H