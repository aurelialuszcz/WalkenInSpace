//
//  episode5.hpp
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 28/02/2024.
//

#ifndef episode5_hpp
#define episode5_hpp

#include <stdio.h>
#include "engine.hpp"
#include "texture.hpp"

class Episode5: public GameEngine {
public:
    virtual bool init(const std::string title="Tutorial", int width=1200, int height=800) override;
    virtual void render() override;
    
private:
    Texture mTexture;
};

#endif /* episode5_hpp */
