#include "DisplaceableEntity.h"

DisplaceableEntity::DisplaceableEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities,
Array<Portal*, 2>* portals, float airResistance, float groundResistance) :
DynamicEntity(rect, fileName, texturePack, colEntities, airResistance, groundResistance), portals(portals)
{
}

void DisplaceableEntity::handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders)
{
    handlePortalCollisionEffect(colliders);
    DynamicEntity::handleCollisionEffect(updatedPos, dt, colliders);
}

void DisplaceableEntity::handlePortalCollisionEffect(std::vector<std::pair<Entity*, Collision>>& colliders)
{
    Portal* portal = nullptr;
    Collision collision;
    for(std::pair<Entity*, Collision>& c : colliders)
    {
        portal = dynamic_cast<Portal*>(c.first);
        if(portal != nullptr) 
        {
            collision = c.second;
            break;
        }
    }

    if(portal != nullptr && portal->initialized())
    {
        Portal* destPortal = portal->getType() == Portal::Type::BLUE ? getPortal(Portal::Type::RED) : getPortal(Portal::Type::BLUE);
        if(destPortal->initialized()) gotoPortal(portal, destPortal);
    }
}

void DisplaceableEntity::gotoPortal(Portal* originPortal, Portal* destPortal)
{
    Vector2D pos = destPortal->getRect().pos;
    pos += destPortal->getDirection().setMagnitude( 1.5 * std::min(destPortal->getRect().size.x, destPortal->getRect().size.y) );

    bool validDisplacement = true;
    for(Entity* e : *colEntities)
    {
        if(e != this && Rect(pos, rect.size).intersects(e->getRect()))
        {
            validDisplacement = false;
            break;
        }
    }
    if(validDisplacement) 
    {
        rect.pos = pos;
        float mag = velocity.magnitude();
        velocity = destPortal->getDirection();
        velocity.setMagnitude(mag);
    }
}