#include "text.hpp"
#include "common.hpp"
#include "draw.hpp"

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

static SDL_Texture *fontTexture;
static char         drawTextBuffer[MAX_LINE_LENGTH];

void initFonts(void)
{
    fontTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/font.png");
}

void drawText(int x, int y, int r, int g, int b, char *format, ...)
{
    int      i, len, c;
    SDL_Rect rect;
    va_list  args;

    memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    len = strlen(drawTextBuffer);

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    SDL_SetTextureColorMod(fontTexture, r, g, b);

    for (i = 0; i < len; i++)
    {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z')
        {
            rect.x = (c - ' ') * GLYPH_WIDTH;

            rectangleTwo(fontTexture, &rect, x, y);

            x += GLYPH_WIDTH;
        }
    }
}
