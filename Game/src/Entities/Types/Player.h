#ifndef PLAYER
#define PLAYER

#include <memory>
#include <array>

#include "Portal.h"
#include "DynamicEntity.h"
#include "Array.h"

class Player : public DynamicEntity
{
public:
	Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Array<std::unique_ptr<Portal>, 2>* portal);
	Player(Rect rect, std::vector<Entity*>* colEntity);

	void moveRight() { velocity.x = speed; }
	void moveLeft() { velocity.x = -speed; }
	void stop() { velocity.x = 0; }
	void jump() { if(onGround) velocity.y = -jumpSpeed; onGround = false; }

	void handleCollisionEffect(Collision colType, Direction colDir, std::vector<Entity*>& colliders) override;
	void gotoPortal(Collision colType, Portal* originPortal, Portal* destPortal);

private:
	Portal* getPortal(Portal::Type type);

private:
	float speed = 2;
	float jumpSpeed = 4.1f;

	Array<std::unique_ptr<Portal>, 2>* portal;
};

#endif
