#include "background.hpp"
#include "draw.hpp"
#include "common.hpp"
#include "stage.hpp"

extern App app;
static int backgroundY;
static SDL_Texture *background;

// draw background to screen

void initBackground(void)
{
    background = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/background_.png");

    backgroundY = 0;
}

void drawBackground(void)
{
    SDL_Rect dest;
    int      y;

    for (y = backgroundY; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT)
    {
        dest.x = 0;
        dest.y = y;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}


void doBackground(void)
{
    if (--backgroundY < -SCREEN_HEIGHT)
    {
        backgroundY = 0;
    }
}
