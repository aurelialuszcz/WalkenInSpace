//
//  Map.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef Map_h
#define Map_h
#include "Game.hpp"
#include "SDL.h"

class Map {
    
public:
    
    Map();
    ~Map();
    
    void LoadMap(int arr[20][25]);
    void DrawMap();
    
private:
    
    SDL_Rect src, dest;
    SDL_Texture*  brownMatter;
    SDL_Texture* greenMatter;
    SDL_Texture* space;
    
    int map[20][25];
};

#endif /* Map_h */
