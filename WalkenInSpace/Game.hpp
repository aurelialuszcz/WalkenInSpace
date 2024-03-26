

#ifndef Game_hpp
#define Game_hpp
#include "SDL.h"
#include <stdio.h>
#include "GameObject.hpp"
#include "Textures.hpp"

class Game {
    
public:
    Game();
    ~Game();
    
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; };
    static SDL_Renderer *renderer;
    
private:
    bool isRunning;
    SDL_Window *window;
    int count = 0;
};


#endif /* Game_hpp */