//
//  Textures.hpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 13/03/2024.
//

#ifndef Textures_hpp
#define Textures_hpp

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.hpp"

class Textures {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

#endif /* Textures_hpp */
