#ifndef PORTAL_PROJECTILE
#define PORTAL_PROJECTILE

#include "DynamicEntity.h"
#include "Portal.h"

#define SPEED 4

class PortalProjectile : public DynamicEntity
{
public:

	PortalProjectile(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Portal::Type type);
	PortalProjectile(Rect rect, std::vector<Entity*>* colEntity);

    void shoot(Vector2D direction);
    Portal::Type getType() { return type; };
    
private:

    void handleCollisionEffect(Collision colType) override;

public:

    Portal::Type type;
    Collision collision = Collision::NON;
};

#endif