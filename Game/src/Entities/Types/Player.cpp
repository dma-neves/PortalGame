#include "Player.h"

Player::Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* dynamicEntities,
Array<std::unique_ptr<Portal>, 2>* portals) :
DynamicEntity(rect, fileName, texturePack, dynamicEntities), portals(portals)
{
}

void Player::handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders)
{
    handlePortalCollisionEffect(colliders);
    DynamicEntity::handleCollisionEffect(updatedPos, dt, colliders);
}

void Player::handlePortalCollisionEffect(std::vector<std::pair<Entity*, Collision>>& colliders)
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

void Player::gotoPortal(Portal* originPortal, Portal* destPortal)
{
    this->getRect().pos = destPortal->getRect().pos;
    this->getRect().pos += destPortal->getDirection().setMagnitude( 1.5 * std::min(destPortal->getRect().size.x, destPortal->getRect().size.y) );

    float mag = velocity.magnitude();
    velocity = destPortal->getDirection();
    velocity.setMagnitude(mag);
}