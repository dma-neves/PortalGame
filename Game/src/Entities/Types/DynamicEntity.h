#ifndef DYNAMIC_ENTITY
#define DYNAMIC_ENTITY

#include <vector>
#include <utility>
#include <iostream>

#include "Entity.h"

#define DEFAULT_GRAVITY 2
#define DEFAULT_AIR_RESISTANCE 0.002
#define DEFAULT_GROUND_RESISTANCE 0.06

class Collision
{
public:
	enum Type      {VERTICAL = 0, HORIZONTAL, NON};
	enum Direction {UP, DOWN, LEFT, RIGHT, UNDEFINED};

	Collision(Type type = NON, Direction direction = UNDEFINED) : type(type), direction(direction) {}

	Type type;
	Direction direction;
	bool diagonal = false;
};

class DynamicEntity : public Entity
{
public:
	DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities, 
	float airResistance = DEFAULT_AIR_RESISTANCE, float groundResistance = DEFAULT_GROUND_RESISTANCE, float gravity = DEFAULT_GRAVITY);

	void update(float dt) override;
	void handleCollision(Vector2D updatedPos, float dt);
	virtual void handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders);

	bool isOnGround() { return onGround; }

private:
	Collision getCollision(Rect& dRect, Rect& cRect, Vector2D& updatedPos);

public:
	Vector2D velocity;
	Vector2D acceleration;

private:
	float gravity;
	float airResistance;
	float groundResistance;

protected:
	std::vector<Entity*>* colEntities; //Collidable Entity
	bool onGround = false;
};

#endif
