
#include "Game.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Textures.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());

Game::Game() {};
Game::~Game() {};

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen) {
    
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    // SDL initialisation
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialised" << std::endl;
        
        //window creatiom
        window = SDL_CreateWindow("Walken In Space", x, y, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }
        
        //renderer creation
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        
        isRunning = true;
        
    } 

    // map creation (background)
    map = new Map();
    // player object creation
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/player.PNG");
    player.addComponent<KeyboardController>();
    
}

void Game::handleEvents() {
    
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    
    manager.refresh();
    manager.update();

}

void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
