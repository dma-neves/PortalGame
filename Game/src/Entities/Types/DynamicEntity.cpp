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
	Collision colType = NON;

	for(int i = 0; i < colEntity->size() && !velocity.null(); i++)
	{
		Entity* e = (*colEntity)[i];
		if(e != this && updatedRect.intersects(e->getRect()))
		{
			Collision c = collisionType(rect, e->getRect());
			if(c == DIAGONAL && colType == NON) colType = c;

			else if(c != DIAGONAL) colType = c;

			if(colType == HORIZONTAL)    { velocity.x = 0; }
			else if(colType == VERTICAL) { velocity.y = 0; }

			if(colType == VERTICAL && rect.pos.y < e->getRect().pos.y) onGround = true;
		}
	}

	if(colType == DIAGONAL) velocity = 0;
	if(velocity.y > 0) onGround = false;

	handleCollisionEffect(colType);
}

DynamicEntity::Collision DynamicEntity::collisionType(Rect& dRect, Rect& cRect)
{
	Collision colType = NON;

	bool stat_a = dRect.getOrigin().y <= cRect.pos.y + cRect.size.y/2.f;
	bool stat_b = cRect.getOrigin().y <= dRect.pos.y + dRect.size.y/2.f;
	if(stat_a && stat_b)
	{
		colType = HORIZONTAL;
	}

	stat_a = dRect.getOrigin().x <= cRect.pos.x + cRect.size.x/2.f;
	stat_b = cRect.getOrigin().x <= dRect.pos.x + dRect.size.x/2.f;
	if(stat_a && stat_b)
	{
		if(colType == HORIZONTAL) colType = DIAGONAL;
		else                      colType = VERTICAL;
	}

	if(colType == NON) colType = DIAGONAL;
	return colType;
}
