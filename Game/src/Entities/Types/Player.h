#ifndef PLAYER
#define PLAYER

#include "DynamicEntity.h"

class Player : public DynamicEntity
{
public:
	Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity);
	Player(Rect rect, std::vector<Entity*>* colEntity);

	void moveRight() { velocity.x = speed; }
	void moveLeft() { velocity.x = -speed; }
	void stop() { velocity.x = 0; }
	void jump() { if(onGround) velocity.y = -jumpSpeed; onGround = false; }

private:
	float speed = 2;
	float jumpSpeed = 4.1f;
};

#endif
