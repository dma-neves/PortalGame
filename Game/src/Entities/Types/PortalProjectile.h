#ifndef PORTAL_PROJECTILE
#define PORTAL_PROJECTILE

#include "DynamicEntity.h"
#include "Portal.h"

#define SPEED 4
#define LIFE_SPAN 8

class PortalProjectile : public DynamicEntity
{
public:

	PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Portal::Type type);
	PortalProjectile(Rect rect, std::vector<Entity*>* colEntity);

    void update(float dt) override;

    void shoot(Vector2D direction);
    Portal::Type getType() { return type; };

    Direction getCollisionDirection() { return collisionDir; }
    
private:

    void handleCollisionEffect(Collision colType, Direction colDir) override;

public:

    Portal::Type type;
    Collision collision = Collision::NON;
    Direction collisionDir = Direction::UNDEFINED;

private:

    float timer = 0;
};

#endif