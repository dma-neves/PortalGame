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
	enum Collision {VERTICAL = 0, HORIZONTAL, NON};
	enum Direction {UP, DOWN, LEFT, RIGHT, UNDEFINED};

	DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY);
	DynamicEntity(Rect rect, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY);

	void update(float dt) override;
	void handleCollision(Vector2D updatedPos);
	virtual void handleCollisionEffect(Collision colType, Direction colDir) {}

private:
	float gravity;
	std::vector<Entity*>* colEntity; //Collidable Entity

	std::pair<Collision, Direction> getCollision(Rect& dRect, Rect& cRect, Vector2D& updatedPos);

protected:
	Vector2D velocity;
	Vector2D acceleration = Vector2D(0, gravity);

	bool onGround = false;
};

#endif
