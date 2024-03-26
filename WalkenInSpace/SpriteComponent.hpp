//
//  SpriteComponent.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef SpriteComponent_h
#define SpriteComponent_h
#include "Components.hpp"
#include "SDL.h"
#include "Textures.hpp"

class SpriteComponent : public Component {
    
private:
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    
public:
    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        
        setTex(path);
    }
    
    // for when needing to change the path of a sprite
    void setTex(const char* path) {
        texture = Textures::LoadTexture(path);
    }
    
    void init() override {
        
        position = &entity->getComponent<PositionComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 64;
        
    }
    
    void update() override {
        
        destRect.x = position->x();
        destRect.y = position->y();
        
    }
    
    void draw() override {
        
        Textures::Draw(texture, srcRect, destRect);
        
    }
};

#endif /* SpriteComponent_h */
