

#include "Textures.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.hpp"
#include "GameObject.hpp"

SDL_Texture* Textures::LoadTexture(const char* texture) {

    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}

void Textures::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
