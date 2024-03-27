//
//  Map.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#include <stdio.h>
#include "Map.hpp"
#include "SDL.h"
#include "Game.hpp"
#include <fstream>

Map::Map() {

};

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    // char by char read the file
    char tile;
    // object to store the file
    std::fstream mapFile;
    mapFile.open(path);
    
    // pass the file
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            Game::AddFile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore();
        }
    }
    
    mapFile.close();
    
}
