//
//  ECS.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 27/03/2024.
//

#include <stdio.h>
#include "ECS.hpp"

void Entity::addGroup(Group mGroup) {
    
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
    
}
