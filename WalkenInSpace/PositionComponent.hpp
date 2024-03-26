//
//  PositionComponent.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef PositionComponent_h
#define PositionComponent_h
#include "Components.hpp"

class PositionComponent : public Component {
private:
    int xpos;
    int ypos;
    
public:
    
    // default starts at position 0,0
    PositionComponent() {
        xpos = 0;
        ypos = 0;
    }
    
    PositionComponent(int x, int y) {
        
        xpos = x;
        ypos = y;
        
    }
    
    void update() override {
        xpos++;
        ypos++;
    }
    
    int x() { return xpos; }
    void x(int x) { xpos = x; }
    int y() { return ypos; }
    void y(int y) { ypos = y; }
    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }
};

#endif /* PositionComponent_h */
