//
//  main.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 05/02/2024.
//

#include "stb_image.h"
#include <iostream>
#include "SDL.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Game.hpp"

Game *game = nullptr;

int main( int argc, char* args[] )
{
    
    /*const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint64 frameStart;
    int frameTime;*/
    
    game = new Game();
    
    game->init("Walken in space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    
    while (game->running()) {
        
        //frameStart = SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();
        
        /*frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay < frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }*/
    }
    
    game->clean();
    
    return 0;
}
