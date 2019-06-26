#include "DynamicEntity.h"
#include "StaticBlock.h"
#include "Player.h"

DynamicEntity::DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* dynamicEntities, 
float gravity, float resistance) :
Entity(rect, fileName, texturePack), 
gravity(gravity),
resistance(resistance),
dynamicEntities(dynamicEntities)
{
	acceleration = Vector2D(0, gravity);
}

void DynamicEntity::update(float dt)
{
	velocity += acceleration*dt;
	std::abs(velocity.x) - resistance < 0 ? velocity.x = 0 : velocity.x -= (velocity.x < 0 ? -1 : 1) * resistance;

	if(!(velocity*dt).null())
	{
		Vector2D updatedPos = rect.pos + velocity*dt;
		handleCollision(updatedPos, dt);

		rect.pos += velocity*dt;
	}
}

void DynamicEntity::handleCollision(Vector2D updatedPos, float dt)
{
	Rect updatedRect = rect;
	updatedRect.pos = updatedPos;
	Collision collision = Collision();
	std::vector<std::pair<Entity*, Collision>> colliders;

	for(Entity* e : *dynamicEntities)
	{
		if(e != this && updatedRect.intersects(e->getRect()))
		{
			collision = getCollision(rect, e->getRect(), updatedPos);
			colliders.push_back( {e, collision} );

			if(dynamic_cast<StaticBlock*>(e) != nullptr || dynamic_cast<Player*>(e) != nullptr)
			{
				if(collision.type == Collision::Type::HORIZONTAL)    { velocity.x = 0; }
				else if(collision.type == Collision::Type::VERTICAL) { velocity.y = 0; }
			}

			if(collision.type == Collision::Type::VERTICAL && rect.pos.y < e->getRect().pos.y) onGround = true;
		}
		if(velocity.y > 0) onGround = false;
	}
	handleCollisionEffect(updatedPos, dt, colliders);
}

Collision DynamicEntity::getCollision(Rect& dRect, Rect& cRect, Vector2D& updatedPos)
{
	Collision collision = Collision();

	bool vertical = false;
	Rect vUpdatedRect = dRect;
	vUpdatedRect.pos.y = updatedPos.y;
	if(vUpdatedRect.intersects(cRect))
	{
		vertical = true;
		collision.type = Collision::Type::VERTICAL;
		collision.direction = updatedPos.y > dRect.pos.y ? Collision::Direction::DOWN : Collision::Direction::UP;
	}

	vUpdatedRect.pos = Vector2D(updatedPos.x, dRect.pos.y);
	if(vUpdatedRect.intersects(cRect))
	{
		if(vertical) collision.diagonal = true;
		collision.type = Collision::Type::HORIZONTAL;
		collision.direction = updatedPos.x > dRect.pos.x ? Collision::Direction::RIGHT : Collision::Direction::LEFT;
	}

	return collision;
}

void DynamicEntity::handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders)
{
	Rect updatedRect = rect;
	updatedRect.pos = updatedPos;

	for(std::pair<Entity*, Collision>& c : colliders)
	{
		if(dynamic_cast<DynamicBlock*>(c.first) != nullptr)
		{
			DynamicEntity* dEntity = dynamic_cast<DynamicEntity*>(c.first);

			if(c.second.diagonal) dEntity->velocity = velocity;
			else c.second.type == Collision::Type::HORIZONTAL ? dEntity->velocity.x = velocity.x : dEntity->velocity.y = velocity.y;
			dEntity->handleCollision(dEntity->getRect().pos + dEntity->velocity*dt, dt);
			dEntity->getRect().pos += dEntity->velocity*dt;

			if(updatedRect.intersects(dEntity->getRect()))
			{
				if(c.second.diagonal) velocity = 0;

				else if(c.second.type == Collision::Type::HORIZONTAL) velocity.x = 0;

				else velocity.y = 0;

				if(c.second.type == Collision::Type::VERTICAL && rect.pos.y < dEntity->getRect().pos.y) onGround = true;
			}
			if(velocity.y > 0) onGround = false;
		}
	}
}
