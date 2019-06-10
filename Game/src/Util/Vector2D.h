#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0);
    Vector2D(sf::Vector2f vec);
    Vector2D(sf::Vector2i vec);
    Vector2D(sf::Vector2u vec);

    float x, y;

    Vector2D operator+(Vector2D addVector);
    Vector2D operator-(Vector2D subVector);
    Vector2D operator*(float scaler);
    Vector2D operator/(float scaler);

    void operator+=(Vector2D addVector);
    void operator-=(Vector2D subVector);
    void operator*=(float scaler);
    void operator/=(float scaler);
    void operator=(float num);

    bool operator==(Vector2D vec) { return (x == vec.x && y == vec.y); }
    bool operator!=(Vector2D vec) { return (x != vec.x && y != vec.y); }

    Vector2D& setMagnitude(float mag);
    float magnitude();
    bool null();
    float angle(Vector2D vec);
    void rotate(float angle);

    sf::Vector2f sfVector() { return sf::Vector2f(x, y); }
};

#endif // VECTOR2D_H
