#ifndef PLAYER
#define PLAYER

#include <memory>
#include <array>

#include "Portal.h"
#include "DynamicBlock.h"
#include "Array.h"

class Player : public DynamicEntity
{
public:
	Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, Array<std::unique_ptr<Portal>, 2>* portal);

	void moveRight() { velocity.x = speed; }
	void moveLeft() { velocity.x = -speed; }
	void stop() { velocity.x = 0; }
	void jump() { if(onGround) velocity.y = -jumpSpeed; onGround = false; }

	void handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders) override;

private:
	Portal* getPortal(Portal::Type type) { return (*portal)[type].get(); }

	void handlePortalCollisionEffect(std::vector<std::pair<Entity*, Collision>>& colliders);
	void gotoPortal(Portal* originPortal, Portal* destPortal);

private:
	float speed = 2;
	float jumpSpeed = 4.1f;

	Array<std::unique_ptr<Portal>, 2>* portal;
};

#endif
