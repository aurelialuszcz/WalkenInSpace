
#include "Game.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Textures.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

bool Game::isRunning = false;

enum groupLabels : std::size_t {
    
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
    
};

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
    
    Map::LoadMap("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/pxyel_16x16.map", 16, 16);
    
    // player object creation
    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/player.PNG");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/dirt.PNG");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);
    
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

    for (auto cc : colliders) {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    for (auto& p : players) {
        p->draw();
    }
    for (auto& e : enemies) {
        e->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::AddFile(int id, int x, int y) {
    
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}
