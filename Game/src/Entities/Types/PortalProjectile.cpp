#include "PortalProjectile.h"

PortalProjectile::PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Portal::Type type) :
DynamicEntity(rect, fileName, texturePack, colEntity, 0), type(type)
{
}

PortalProjectile::PortalProjectile(Rect rect, std::vector<Entity*>* colEntity) : DynamicEntity(rect, colEntity)
{
}

void PortalProjectile::update(float dt)
{
    timer += dt;
    if(timer >= LIFE_SPAN) kill();

    else DynamicEntity::update(dt);
}

void PortalProjectile::shoot(Vector2D direction)
{
    velocity = direction;
    velocity.setMagnitude(SPEED);
}

void PortalProjectile::handleCollisionEffect(Collision colType, Direction colDir)
{
    collision = colType;
    collisionDir = colDir;
}