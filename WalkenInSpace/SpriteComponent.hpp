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
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    
    
public:
    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        
        setTex(path);
    }
    
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }
    
    // for when needing to change the path of a sprite
    void setTex(const char* path) {
        texture = Textures::LoadTexture(path);
    }
    
    void init() override {
        
        transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        
    }
    
    void update() override {
        
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }
    
    void draw() override {
        
        Textures::Draw(texture, srcRect, destRect);
        
    }
};

#endif /* SpriteComponent_h */
