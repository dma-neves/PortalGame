#include "DynamicEntity.h"
#include "StaticBlock.h"

DynamicEntity::DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, float gravity, float resistance) :
Entity(rect, fileName, texturePack), 
gravity(gravity),
resistance(resistance),
colEntity(colEntity)
{
}

DynamicEntity::DynamicEntity(Rect rect, std::vector<Entity*>* colEntity, float gravity, float resistance) : 
Entity(rect), 
colEntity(colEntity), 
gravity(gravity),
resistance(resistance)
{
}

void DynamicEntity::update(float dt)
{
	velocity += acceleration*dt;
	std::abs(velocity.x) - resistance < 0 ? velocity.x = 0 : velocity.x -= (velocity.x < 0 ? -1 : 1) * resistance;

	if(!(velocity*dt).null())
	{
		Vector2D updatedPos = rect.pos + velocity*dt;
		handleCollision(updatedPos);

		rect.pos += velocity*dt;
	}
}

void DynamicEntity::handleCollision(Vector2D updatedPos)
{
	Rect updatedRect = rect;
	updatedRect.pos = updatedPos;

	Collision colType = Collision::NON;
	Direction colDir = Direction::UNDEFINED;
	std::vector<Entity*> colliders;

	for(int i = 0; i < colEntity->size() && !velocity.null(); i++)
	{
		Entity* e = (*colEntity)[i];
		if(e != this && updatedRect.intersects(e->getRect()))
		{
			colliders.push_back(e);
			std::pair<Collision, Direction> collsion = getCollision(rect, e->getRect(), updatedPos);
			colType = collsion.first;
			colDir = collsion.second;

			if(dynamic_cast<StaticBlock*>(e) != nullptr)
			{
				if(colType == HORIZONTAL)    { velocity.x = 0; }
				else if(colType == VERTICAL) { velocity.y = 0; }
			}

			if(colType == VERTICAL && rect.pos.y < e->getRect().pos.y) onGround = true;
		}
	}
	if(velocity.y > 0) onGround = false;

	if(colType != Collision::NON) handleCollisionEffect(colType, colDir, colliders);
}

std::pair<DynamicEntity::Collision, DynamicEntity::Direction> DynamicEntity::getCollision(Rect& dRect, Rect& cRect, Vector2D& updatedPos)
{
	Collision colType = Collision::NON;
	Direction colDir = Direction::UNDEFINED;

	Rect vUpdatedRect = dRect;
	vUpdatedRect.pos.y = updatedPos.y;
	if(vUpdatedRect.intersects(cRect))
	{
		colType = VERTICAL;
		colDir = updatedPos.y > dRect.pos.y ? DOWN : UP;
	}

	vUpdatedRect.pos = Vector2D(updatedPos.x, dRect.pos.y);
	if(vUpdatedRect.intersects(cRect))
	{
		colType = HORIZONTAL;
		colDir = updatedPos.x > dRect.pos.x ? RIGHT : LEFT;
	}

	return std::pair<Collision, Direction> (colType, colDir);
}
