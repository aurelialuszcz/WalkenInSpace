//
//  GameObject.hpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 13/03/2024.
//
#include "SDL.h"
#include "SDL_image.h"
#include "Game.hpp"

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>

class GameObject {
  
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();
    
    void Update();
    void Render();
    
private:
    int xpos;
    int ypos;
    
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif /* GameObject_hpp */
