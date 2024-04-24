#ifndef draw_hpp
#define draw_hpp

#include <stdio.h>
#include "SDL_image.h"
#include "SDL.h"

void prepareScene(void);
void presentScene(void);
SDL_Texture *loadTexture(char *filename);
void rectangle(SDL_Texture *texture, int x, int y);
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

#endif /* draw_hpp */
