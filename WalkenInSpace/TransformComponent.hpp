//
//  PositionComponent.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef PositionComponent_h
#define PositionComponent_h
#include "Components.hpp"
#include "Vector2D.hpp"

// this could be struct
// struct : everything by default is public
// class : everything by default is private

class TransformComponent : public Component {

public:
    
    Vector2D position;
    Vector2D velocity;
    
    int height = 32;
    int width = 32;
    int scale = 1;
    
    int speed = 3;
    
    
    // default starts at position 0,0
    TransformComponent() {
        position.Zero();
    }
    
    TransformComponent(float x, float y) {
        
        position.Zero();
        
    }
    
    TransformComponent(int sc) {
        
        position.Zero();
        scale = sc;
        
    }
    
    TransformComponent(float x, float y, int h, int w, int sc) {
        
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
        
    }
    
    void init() override {
        
        velocity.Zero();
        
    }
    
    void update() override {
      
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif /* PositionComponent_h */
