#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) : x(x), y(y)
{
}

Vector2D::Vector2D(sf::Vector2f vec)
{
    x = vec.x;
    y = vec.y;
}

Vector2D::Vector2D(sf::Vector2u vec)
{
    x = vec.x;
    y = vec.y;
}

Vector2D::Vector2D(sf::Vector2i vec)
{
    x = vec.x;
    y = vec.y;
}

Vector2D Vector2D::operator+(Vector2D vec)
{
    return Vector2D(x + vec.x, y + vec.y);
}

Vector2D Vector2D::operator-(Vector2D vec)
{
    return Vector2D(x - vec.x, y - vec.y);
}

Vector2D Vector2D::operator*(float scaler)
{
    return Vector2D(x * scaler, y * scaler);
}

Vector2D Vector2D::operator/(float scaler)
{
    return Vector2D(x / scaler, y / scaler);
}

void Vector2D::operator+=(Vector2D vec)
{
    x += vec.x;
    y += vec.y;
}

void Vector2D::operator-=(Vector2D vec)
{
    x -= vec.x;
    y -= vec.y;
}

void Vector2D::operator*=(float scaler)
{
    x *= scaler;
    y *= scaler;
}

void Vector2D::operator/=(float scaler)
{
    x /= scaler;
    y /= scaler;
}

void Vector2D::operator=(float num)
{
    if(num == 0)
    {
        x = 0;
        y = 0;
    }
    else std::cout << "Error: Invalid Vector2D operation: Vector2D = " << num << std::endl;
}

float Vector2D::magnitude()
{
    return sqrt( pow(x,2) + pow(y,2) );
}

bool Vector2D::null()
{
   return (x == 0 and y == 0);
}

float Vector2D::angle(Vector2D vec)
{
    float c = (x*vec.x + y*vec.y) / (magnitude() * vec.magnitude());

    if(c >= -1 and c <= 1) return acos(c);

    else std::cout << "Error: Invalid cos value: " << c << std::endl;

    return 0;
}

void Vector2D::rotate(float angle)
{
    float v_x = x * cos(angle) - y * sin(angle);
    float v_y = x * sin(angle) + y * cos(angle);

    x = v_x;
    y = v_y;
}
