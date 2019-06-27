#include "PortalProjectile.h"

PortalProjectile::PortalProjectile(Rect rect, std::string fileName, std::string texturePack,
Portal::Type type, std::vector<Entity*>* colEntities, Array<std::unique_ptr<Portal>, 2>* portals, bool* resize) :
DynamicEntity(rect, fileName, texturePack, colEntities, 0, 0), type(type), portals(portals), resize(resize)
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

void PortalProjectile::handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders)
{
    Collision collision;
    for(std::pair<Entity*, Collision>& c : colliders)
    {
        if(dynamic_cast<StaticBlock*>(c.first) == nullptr)
        {
            this->kill();
            return;
        }
        collision = c.second;
    }

    if(collision.type != Collision::Type::NON) repositionPortal(collision);
}

void PortalProjectile::repositionPortal(Collision& collision)
{
    Vector2D direction;
    switch(collision.direction)
    {
        case Collision::Direction::UP: direction.y = 1; break;

        case Collision::Direction::DOWN: direction.y = -1; break;

        case Collision::Direction::LEFT: direction.x = 1; break;

        case Collision::Direction::RIGHT: direction.x = -1; break;
    }

    (*portals)[getType()]->reposition( getRect().pos, direction );
    Rect& portalRect = (*portals)[getType()]->getRect();
    float dim = std::min(portalRect.size.x, portalRect.size.y);
    portalRect.size = collision.type == Collision::Type::HORIZONTAL ? Vector2D(dim, dim*2) : Vector2D(dim*2, dim);
    *resize = true;

    kill();
}