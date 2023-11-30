#include "main.h"
#include "grid.h"

/*
To change the brightness, divide R, G and B through a number larger than 1 to make it darker,
or multiply them with that number to make it brighter. If the color component becomes higher
than 255, truncate it to 255.
*/
Color ChangeColorBrightness(Color color, float brightness)
{
    Color newColor;
    newColor.r = MIN(color.r * brightness, 255);
    newColor.g = MIN(color.g * brightness, 255);
    newColor.b = MIN(color.b * brightness, 255);
    newColor.a = color.a;
    return newColor;
}

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
Button *CreateButton(float buttonHeight, float buttonWidth, float posX, float posY, char *text, const char *texturePath, const char *textureHoverPath, Color col)
{
    Button *newButton = (Button *)malloc(sizeof(Button));
    Rectangle rectPos;

    rectPos.height = buttonHeight;
    rectPos.width = buttonWidth;
    rectPos.x = posX;
    rectPos.y = posY;

    newButton->rect = rectPos;
    newButton->text = text;
    newButton->state = NORMAL;

    if (texturePath != NULL)
    {
        newButton->texture = LoadTexture(texturePath);
        if (textureHoverPath != NULL)
        {
            newButton->textureHover = LoadTexture(textureHoverPath);
        }
        newButton->useTexture = 1;
    }
    else
    {
        newButton->col = col;
        newButton->useTexture = 0;
    }

    return newButton;
}

void DrawButton(Button *button)
{
    Color color = button->col;
    Texture2D texture = button->texture;

    switch (button->state)
    {
    case NORMAL:
        break;

    case HOVER:
        if (button->useTexture)
        {
            texture = button->textureHover;
        }
        else
        {
            color = ChangeColorBrightness(color, 1.2);
        }
        break;
    case PRESSED:
        if (button->useTexture)
        {
            texture = button->texturePressed;
        }
        else
        {
            color = ChangeColorBrightness(color, 0.8);
        }
        break;
    }

    if (button->useTexture)
    {
        DrawTexture(texture, button->rect.x, button->rect.y, WHITE);
    }
    else
    {
        DrawRectangle(button->rect.x, button->rect.y, button->rect.width, button->rect.height, color);
    }

    if (button->text != NULL)
    {
        DrawText(button->text, button->rect.x + (button->rect.width / 2) - (MeasureText(button->text, 20) / 2), button->rect.y + (button->rect.height / 2) - 10, 20, BLACK);
    }
}

void CheckButtonState(Button *button, Vector2 mousePoint)
{
    Rectangle rect = button->rect;
    if (CheckCollisionPointRec(mousePoint, rect))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            button->state = PRESSED;
        }
        else
        {
            button->state = HOVER;
        }
    }
    else
    {
        button->state = NORMAL;
    }
}

void ButtonOne(Button ***buttons, int *nbButtons)
{
    if (*nbButtons == 2)
    {
        INFO_LOG("Button one pressed, deleting button two");
        free((*buttons)[1]);
        *nbButtons = 1;
        *buttons = (Button **)realloc(*buttons, *nbButtons * sizeof(Button *));
        return;
    }

    INFO_LOG("Button one pressed");
    *nbButtons = 2;
    *buttons = (Button **)realloc(*buttons, *nbButtons * sizeof(Button *));
    (*buttons)[*nbButtons - 1] = CreateButton(100, 300, (*buttons)[0]->rect.x, (*buttons)[0]->rect.y + (*buttons)[0]->rect.height, "Hello there", NULL, NULL, BLUE);
}

void ButtonTwo(Button ***buttons, int *nbButtons)
{
    if (*nbButtons == 3)
    {
        INFO_LOG("Button two pressed, deleting button three");
        free((*buttons)[2]);
        *nbButtons = 2;
        *buttons = (Button **)realloc(*buttons, *nbButtons * sizeof(Button *));
        return;
    }

    INFO_LOG("Button two pressed");
    *nbButtons = 3;
    *buttons = (Button **)realloc(*buttons, *nbButtons * sizeof(Button *));
    (*buttons)[*nbButtons - 1] = CreateButton(100, 300, (*buttons)[1]->rect.x, (*buttons)[1]->rect.y + (*buttons)[1]->rect.height, "General Kenobi", NULL, NULL, GREEN);
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