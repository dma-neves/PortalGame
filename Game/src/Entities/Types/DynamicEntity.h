#ifndef DYNAMIC_ENTITY
#define DYNAMIC_ENTITY

#include <vector>
#include <utility>
#include <iostream>

#include "Entity.h"

#define DEFAULT_GRAVITY 2

class DynamicEntity : public Entity
{
public:
	enum Collision {VERTICAL = 0, HORIZONTAL, DIAGONAL, NON};

	DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY);
	DynamicEntity(Rect rect, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY);

	void update(float dt) override;
	void handleCollision(Vector2D updatedPos);
	virtual void handleCollisionEffect(Collision colType) {}

private:
	float gravity;
	std::vector<Entity*>* colEntity; //Collidable Entity

	Collision collisionType(Rect& dRect, Rect& cRect);

protected:
	Vector2D velocity;
	Vector2D acceleration = Vector2D(0, gravity);

	bool onGround = false;
};

#endif
