#include "DynamicEntity.h"

DynamicEntity::DynamicEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity, float gravity) :
Entity(rect, fileName, texturePack), 
gravity(gravity),
colEntity(colEntity)
{
}

DynamicEntity::DynamicEntity(Rect rect, std::vector<Entity*>* colEntity, float gravity) : Entity(rect), colEntity(colEntity), gravity(gravity)
{
}

void DynamicEntity::update(float dt)
{
	velocity += acceleration*dt;

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

	for(int i = 0; i < colEntity->size() && !velocity.null(); i++)
	{
		Entity* e = (*colEntity)[i];
		if(e != this && updatedRect.intersects(e->getRect()))
		{
			std::pair<Collision, Direction> collsion = getCollision(rect, e->getRect(), updatedPos);
			colType = collsion.first;
			colDir = collsion.second;

			if(colType == HORIZONTAL)    { velocity.x = 0; }
			else if(colType == VERTICAL) { velocity.y = 0; }

			if(colType == VERTICAL && rect.pos.y < e->getRect().pos.y) onGround = true;
		}
	}
	if(velocity.y > 0) onGround = false;

	if(colType != Collision::NON) handleCollisionEffect(colType, colDir);
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
