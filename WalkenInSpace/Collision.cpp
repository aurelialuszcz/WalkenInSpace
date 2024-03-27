//
//  Collision.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#include <stdio.h>
#include "Collision.hpp"
#include "SDL.h"
#include "ColliderComponent.hpp"

// collision class from scratch - could instead use SDL_IntersectRect function

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
        ) {
            return true;
        }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
    
    if (AABB(colA.collider, colB.collider)) {
        std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    } else {
        return false;
    }
}
