#ifndef GATE
#define GATE

#include "StaticBlock.h"

class Gate : public StaticBlock
{
public:

    Gate(Rect rect, std::string fileName, std::string texturePack) : StaticBlock(rect, fileName, texturePack) {}

    void render(sf::RenderWindow& window, Vector2D drawPos) override
    {
        if(closed) Entity::render(window, drawPos);
    }

    bool closed = true;
};

#endif