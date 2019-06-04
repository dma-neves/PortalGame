#include "PortalProjectile.h"

PortalProjectile::PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Portal::Type type) :
DynamicEntity(rect, fileName, texturePack, colEntity, 0), type(type)
{
}

PortalProjectile::PortalProjectile(Rect rect, std::vector<Entity*>* colEntity) : DynamicEntity(rect, colEntity)
{
}

void PortalProjectile::shoot(Vector2D direction)
{
    velocity = direction;
    velocity.setMagnitude(SPEED);
}

void PortalProjectile::handleCollisionEffect(Collision colType)
{
    collision = colType;
}