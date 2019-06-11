#ifndef PORTAL
#define PORTAL

#include "Entity.h"

class Portal : public Entity
{
public:
    enum Type {RED = 0, BLUE};

    Portal(Rect rect, std::string fileName, std::string texturePack, Type type);
    Portal(Rect rect, Type type);

    Type getType() { return type; }
    void reposition(Vector2D pos, Vector2D direction)
    {
        this->getRect().pos = pos;
        this->direction = direction;
    }

private:
    Type type;
    Vector2D direction;
};

#endif
