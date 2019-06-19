#ifndef DYNAMIC_ENTITY
#define DYNAMIC_ENTITY

#include <vector>
#include <utility>
#include <iostream>

#include "Entity.h"

#define DEFAULT_GRAVITY 2
#define DEFAULT_RESISTANCE 0.06

class DynamicEntity : public Entity
{
public:
	enum Collision {VERTICAL = 0, HORIZONTAL, NON};
	enum Direction {UP, DOWN, LEFT, RIGHT, UNDEFINED};

	DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY, float resistance = DEFAULT_RESISTANCE);
	DynamicEntity(Rect rect, std::vector<Entity*>* colEntity, float gravity = DEFAULT_GRAVITY, float resistance = DEFAULT_RESISTANCE);

	void update(float dt) override;
	void handleCollision(Vector2D updatedPos);
	virtual void handleCollisionEffect(Collision colType, Direction colDir, std::vector<Entity*>& colliders) {}

	bool isOnGround() { return onGround; }

private:
	float gravity;
	float resistance;
	std::vector<Entity*>* colEntity; //Collidable Entity

	std::pair<Collision, Direction> getCollision(Rect& dRect, Rect& cRect, Vector2D& updatedPos);

protected:
	Vector2D velocity;
	Vector2D acceleration = Vector2D(0, gravity);

	bool onGround = false;
};

#endif
