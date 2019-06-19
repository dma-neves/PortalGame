#include "Player.h"

Player::Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Array<std::unique_ptr<Portal>, 2>* portal) :
DynamicEntity(rect, fileName, texturePack, colEntity), portal(portal)
{
}

Player::Player(Rect rect, std::vector<Entity*>* colEntity) : DynamicEntity(rect, colEntity)
{
}

void Player::handleCollisionEffect(Collision colType, Direction colDir, std::vector<Entity*>& colliders)
{
    Portal* portal = nullptr;
    for(std::vector<Entity*>::iterator ei = colliders.begin(); ei != colliders.end() && portal == nullptr; ei++)
    {
        portal = dynamic_cast<Portal*>(*ei);
    }

    if(portal != nullptr && portal->initialized())
    {
        Portal* destPortal = portal->getType() == Portal::Type::BLUE ? getPortal(Portal::Type::RED) : getPortal(Portal::Type::BLUE);
        if(destPortal->initialized()) gotoPortal(colType, portal, destPortal);
    }
}

void Player::gotoPortal(Collision colType, Portal* originPortal, Portal* destPortal)
{
    this->getRect().pos = destPortal->getRect().pos;
    this->getRect().pos += destPortal->getDirection().setMagnitude( 1.5 * std::min(destPortal->getRect().size.x, destPortal->getRect().size.y) );

    float mag = velocity.magnitude();
    velocity = destPortal->getDirection();
    velocity.setMagnitude(mag);
}

Portal* Player::getPortal(Portal::Type type)
{
    auto pt = *portal;
    return ( pt[type] ).get();
}