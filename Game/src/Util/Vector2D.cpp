#include "Vector2D.h"

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
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

Vector2D Vector2D::operator+(Vector2D addVector)
{
    Vector2D newVector(this->x + addVector.x, this->y + addVector.y);
    return newVector;
}

Vector2D Vector2D::operator-(Vector2D subVector)
{
    Vector2D newVector(this->x - subVector.x, this->y - subVector.y);
    return newVector;
}

Vector2D Vector2D::operator*(float scaler)
{
    Vector2D newVector(this->x * scaler, this->y * scaler);
    return newVector;
}

Vector2D Vector2D::operator/(float scaler)
{
    Vector2D newVector(this->x / scaler, this->y / scaler);
    return newVector;
}

void Vector2D::operator+=(Vector2D addVector)
{
    this->x += addVector.x;
    this->y += addVector.y;
}

void Vector2D::operator-=(Vector2D subVector)
{
    this->x -= subVector.x;
    this->y -= subVector.y;
}

void Vector2D::operator*=(float scaler)
{
    this->x *= scaler;
    this->y *= scaler;
}

void Vector2D::operator/=(float scaler)
{
    this->x /= scaler;
    this->y /= scaler;
}

void Vector2D::operator=(float num)
{
    if(num == 0)
    {
        this->x = 0;
        this->y = 0;
    }
    else std::cout << "Error: Invalid Vector2D operation: Vector2D = " << num << std::endl;
}

Vector2D& Vector2D::setMagnitude(float mag)
{
    float v_x = x * (mag / magnitude());
    float v_y = y * (mag / magnitude());

    x = v_x;
    y = v_y;

    return *this;
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
    float c = (x*vec.x + y*vec.y) / (this->magnitude() * vec.magnitude());

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
