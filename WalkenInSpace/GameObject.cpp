//
//  GameObject.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 13/03/2024.
//

#include "GameObject.hpp"
#include "Game.hpp"
#include "Textures.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

GameObject::GameObject(const char* textureSheet, int x, int y) {
    
    this->objTexture = Textures::LoadTexture(textureSheet);
    
    this->xpos = x;
    this->ypos = y;
}

void GameObject::Update() {
    
    xpos++;
    ypos++;
    
    srcRect.h = 400;
    srcRect.w = 400;
    srcRect.x = 0;
    srcRect.y = 0;
    
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 64;
    destRect.h = 64;
    
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
