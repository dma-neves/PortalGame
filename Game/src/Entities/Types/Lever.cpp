#include "Lever.h"
#include "DisplaceableEntity.h"

Lever::Lever(Rect rect, std::string fileName, std::string texturePack, Gate* gate, 
std::vector<DisplaceableEntity*>* displaceableEntities) : 
StaticBlock(rect, fileName, texturePack), gate(gate), displaceableEntities(displaceableEntities) 
{
}

void Lever::update(float dt)
{
    bool pressed = false;

    Rect leverRect = rect;
    leverRect.size.setMagnitude( rect.size.magnitude() + COLLISION_MARGIN );

    for(DisplaceableEntity* de : *displaceableEntities)
    {
        if(de->getRect().intersects(leverRect))
        {
            pressed = true;
            break;
        }
    }

    gate->closed = !pressed;
}