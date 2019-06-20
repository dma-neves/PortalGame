#include "PortalProjectile.h"

PortalProjectile::PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity,
Portal::Type type, Array<std::unique_ptr<Portal>, 2>* portal, bool* resize) :
DynamicEntity(rect, fileName, texturePack, colEntity, 0, 0), type(type), portal(portal), resize(resize)
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

void PortalProjectile::handleCollisionEffect(std::pair<Collision, Direction> collision, std::vector<Entity*>& colliders)
{
    for(Entity* e : colliders)
    {
        if(dynamic_cast<Portal*>(e) != nullptr)
        {
            this->kill();
            return;
        }
    }

    if(collision.first != DynamicEntity::Collision::NON) repositionPortal(collision);
}

void PortalProjectile::repositionPortal(std::pair<Collision, Direction>& collision)
{
    Vector2D direction;
    switch(collision.second)
    {
        case DynamicEntity::UP: direction.y = 1; break;

        case DynamicEntity::DOWN: direction.y = -1; break;

        case DynamicEntity::LEFT: direction.x = 1; break;

        case DynamicEntity::RIGHT: direction.x = -1; break;
    }

    (*portal)[getType()]->reposition( getRect().pos, direction );

    Rect& portalRect = (*portal)[getType()]->getRect();
    float dim = std::min(portalRect.size.x, portalRect.size.y);
    portalRect.size = collision.first == DynamicEntity::Collision::HORIZONTAL ? Vector2D(dim, dim*2) : Vector2D(dim*2, dim);
    *resize = true;

    kill();
}