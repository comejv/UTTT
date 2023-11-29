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

#endif // MAIN_H