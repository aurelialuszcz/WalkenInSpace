#include <string>
#include "sdl.hpp"

class GameEngine {
public:
    GameEngine();
    virtual ~GameEngine();
    
    virtual bool init(const std::string title="Test", int width=800, int height=600);
    
    virtual void clear();
    
    virtual void loop();
    
    virtual void handleEvent(SDL_Event &event);
    
    virtual void render() {}
    
    virtual void update() {}
    
public:
    bool success;
    bool quit;
    char errMsg[1024];
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    int width, height;
};

#endif 
