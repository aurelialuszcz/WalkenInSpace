#ifndef util_hpp
#define util_hpp

#include <stdio.h>

int  collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);

#endif /* util_hpp */
