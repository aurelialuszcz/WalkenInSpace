//
//  episode5.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 28/02/2024.
//

#include "episode5.hpp"

bool Episode5::init(const std::string title, int width, int height) {
    GameEngine::init(title, width, height);
    
    mTexture.load(this, "/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/background.PNG");
    
    return success;
}

void Episode5::render() {
    // white background
    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, mTexture.getSDLTexture(), nullptr, nullptr);
    
    SDL_RenderPresent(renderer);
}
