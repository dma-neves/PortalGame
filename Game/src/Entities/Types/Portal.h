#ifndef PORTAL
#define PORTAL

#include "Entity.h"

class Portal : public Entity
{
public:
    enum Type {RED = 0, BLUE};

    Portal(Rect rect, std::string fileName, std::string texturePack, Type type) : Entity(rect, fileName, texturePack), type(type) {}

    void render(sf::RenderWindow& window, Vector2D drawPos) override { if(init) Entity::render(window, drawPos); }

    void reposition(Vector2D pos, Vector2D direction)
    {
        this->getRect().pos = pos;
        this->direction = direction;
        init = true;
    }

    Vector2D getDirection() { return direction; }
    Type getType() { return type; }
    bool initialized() { return init; }

private:
    Type type;
    Vector2D direction;
    bool init = false;
};

#endif
