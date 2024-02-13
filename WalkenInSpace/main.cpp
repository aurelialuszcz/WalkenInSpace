//
//  main.cpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 05/02/2024.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, const char * argv[]) {
   
    sf::RenderWindow window(sf::VideoMode(640, 800), "This is a test");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.display();
    }
    
    return 0;
}
