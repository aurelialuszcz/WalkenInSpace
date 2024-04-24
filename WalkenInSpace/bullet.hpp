#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>

struct Entity;

void initBullets(void);
void doBullets(void);
int bulletHitFighter(Entity *b);
void drawBullets(void);

#endif /* bullet_hpp */
