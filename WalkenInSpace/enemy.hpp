//
//  enemy.hpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 17/04/2024.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
struct Entity;

void fireAlienBullet(Entity *e);
void doEnemies(void);
void drawEnemy(void);
void doFighters(void);
void spawnEnemies(void);

#endif /* enemy_hpp */
