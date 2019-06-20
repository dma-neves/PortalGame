#ifndef PORTAL_PROJECTILE
#define PORTAL_PROJECTILE

#include "DynamicEntity.h"
#include "Portal.h"
#include "Array.h"

#define SPEED 4
#define LIFE_SPAN 8

class PortalProjectile : public DynamicEntity
{
public:

	PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, 
    Portal::Type type, Array<std::unique_ptr<Portal>, 2>* portal, bool* resize);

    void update(float dt) override;

    void shoot(Vector2D direction);
    Portal::Type getType() { return type; };
    
private:

    void handleCollisionEffect(std::pair<Collision, Direction> collision, std::vector<Entity*>& colliders) override;
    void repositionPortal(std::pair<Collision, Direction>& collision);

private:
    Portal::Type type;

    Array<std::unique_ptr<Portal>, 2>* portal;
    bool* resize;
    float timer = 0;
};

#endif