//
//  Vector2D.h
//  WalkenInSpace
//
//  Created by Aurelia Luszcz on 26/03/2024.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp
#include <iostream>


class Vector2D {
public:
    float x;
    float y;
    
    Vector2D();
    Vector2D(float x, float y);
    
    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+= (const Vector2D& vec);
    Vector2D& operator-= (const Vector2D& vec);
    Vector2D& operator*= (const Vector2D& vec);
    Vector2D& operator/= (const Vector2D& vec);

    Vector2D& operator*(const int& i);
    Vector2D& Zero();
    
    friend std::ostream& operator  << (std::ostream& stream, const Vector2D& vec);
    
};

#endif /* Vector2D_h */
