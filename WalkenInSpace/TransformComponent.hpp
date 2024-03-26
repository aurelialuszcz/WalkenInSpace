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
    
    int speed = 3;
    
    
    // default starts at position 0,0
    TransformComponent() {
        position.x = 0.0f;
        position.y = 0.0f;
    }
    
    TransformComponent(float x, float y) {
        
        position.x = x;
        position.y = y;
        
    }
    
    void init() override {
        
        velocity.x = 0;
        velocity.y = 0;
        
    }
    
    void update() override {
      
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif /* PositionComponent_h */
