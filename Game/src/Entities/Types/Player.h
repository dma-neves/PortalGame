#ifndef PLAYER
#define PLAYER

#include <memory>
#include <array>

#include "Portal.h"
#include "DisplaceableEntity.h"
#include "Array.h"

#define AIR_RESISTANCE 0.06

class Player : public DisplaceableEntity
{
public:
	Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities,
	Array<Portal*, 2>* portals);

	void moveRight() { velocity.x = speed; }
	void moveLeft() { velocity.x = -speed; }
	void stop() { velocity.x = 0; }
	void jump() { if(onGround) velocity.y = -jumpSpeed; onGround = false; }

private:
	float speed = 2;
	float jumpSpeed = 4.1f;
};

#endif
