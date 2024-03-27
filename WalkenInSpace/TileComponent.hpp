//
//  TileComponent.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 27/03/2024.
//

#ifndef TileComponent_hpp
#define TileComponent_hpp
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL.h"

class TileComponent : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    SDL_Rect tileRect;
    int tileID;
    char* path;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, int w, int h, int id) {
        
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;
        
        switch (tileID) {
            case 0:
                path = "/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/water.PNG";
                break;
            case 1:
                path = "/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/dirt.PNG";
                break;
            case 2:
                path = "/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/grass.PNG";
                break;
            default:
                break;
        }
    }
    
    void init() override {
        
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();
        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
    
};

#endif /* TileComponent_h */
