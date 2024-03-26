//
//  Map.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#include <stdio.h>
#include "Map.hpp"
#include "SDL.h"
#include "Textures.hpp"

// map for basic space background
int level1[20][25] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

Map::Map() {
    
    brownMatter = Textures::LoadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/dirt.PNG");
    greenMatter = Textures::LoadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/grass.PNG");
    space = Textures::LoadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/water.PNG");

    LoadMap(level1);
    
    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;
    
    dest.x = dest.y = 0;
};

void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            map[row][col] = arr[row][col];
        }
    }
};

void Map::DrawMap()
{
    int type = 0;
    
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            type = map[row][col];
            
            dest.x = col * 32;
            dest.y = row * 32;
            
            switch (type) {
                case 0:
                    Textures::Draw(space, src, dest);
                    break;
                case 1:
                    Textures::Draw(greenMatter, src, dest);
                    break;
                case 2:
                    Textures::Draw(brownMatter, src, dest);
                    break;
                default:
                    break;
            }
        }
    }
};
