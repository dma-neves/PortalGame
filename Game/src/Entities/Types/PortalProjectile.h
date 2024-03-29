#ifndef PORTAL_PROJECTILE
#define PORTAL_PROJECTILE

#include "DynamicEntity.h"
#include "Portal.h"
#include "StaticBlock.h"
#include "Array.h"

#define SPEED 8
#define LIFE_SPAN 8

class PortalProjectile : public DynamicEntity
{
public:

	PortalProjectile(Rect rect, std::string fileName, std::string texturePack, Portal::Type type,
    std::vector<Entity*>* colEntities, Array<Portal*, 2>* portals, bool* resize);

    void update(float dt) override;

    void shoot(Vector2D direction);
    Portal::Type getType() { return type; };
    
private:

    void handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders) override;
    void repositionPortal(Collision& collision);

private:
    Portal::Type type;

    Array<Portal*, 2>* portals;
    bool* resize;
    float timer = 0;
};

#endif