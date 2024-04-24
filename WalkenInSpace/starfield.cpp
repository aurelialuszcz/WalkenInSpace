#include "common.hpp"
#include "starfield.hpp"

static Star stars[MAX_STARS];

extern App app;

// EXTRA - moving stars backgrounds

void initStarfield(void)
{
    int i;

    for (i = 0; i < MAX_STARS; i++)
    {
        stars[i].x = rand() % SCREEN_HEIGHT;
        stars[i].y = rand() % SCREEN_HEIGHT;
        stars[i].speed = 1 + rand() % 8;
    }
}


// EXTRA - moving stars

void doStarfield(void)
{
    int i;

    for (i = 0; i < MAX_STARS; i++)
    {
        stars[i].y += stars[i].speed;

        if (stars[i].y >= SCREEN_HEIGHT)
        {
            stars[i].y = 0;
        }
    }
}


// draw stars to screen

void drawStarfield(void)
{
    int i, c;

    for (i = 0; i < MAX_STARS; i++)
    {
        c = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

        SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x, stars[i].y + 3);
    }
}

