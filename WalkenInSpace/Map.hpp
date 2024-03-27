//
//  Map.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef Map_h
#define Map_h
#include "SDL.h"
#include <iostream>

class Map {
    
public:
    
    Map();
    ~Map();
    
    static void LoadMap(std::string path, int sizeX, int sizeY);
    
};
#endif /* Map_h */
