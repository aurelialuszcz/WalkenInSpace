//
//  Collision.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef Collision_hpp
#define Collision_hpp
#include "SDL.h"

class ColliderComponent;

class Collision {
    
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};

#endif /* Collision_h */
