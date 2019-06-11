#include "EntityManager.h"

EntityManager::EntityManager(bool* resize) : resize(resize)
{
}

void EntityManager::reset()
{
	entity.clear();
	colEntity.clear();
	staticBlock.clear();
}

void EntityManager::update(float dt)
{
	for(Entity* e : entity) 
	{
		e->update(dt);
		handleUpdate(e);
	}
	eraseDeadEntities();
}

Player& EntityManager::addPlayer(Player* player)
{
	this->player.reset(player);

	entity.push_back(player);
	colEntity.push_back(player);
	return *player;
}

Portal& EntityManager::addPortal(Portal* portal)
{
	this->portal[portal->getType()].reset(portal);
	this->entity.push_back(portal);
	return *portal;
}

Entity& EntityManager::addStaticBlock(Entity* staticBlock)
{
	std::unique_ptr<Entity> uptr(staticBlock);
	this->staticBlock.push_back(std::move(uptr));

	this->entity.push_back(staticBlock);
	this->colEntity.push_back(staticBlock);
	return *staticBlock;
}

PortalProjectile& EntityManager::addPortalProjectile(PortalProjectile* portalProjectile)
{
	this->portalProj[portalProjectile->getType()].reset(portalProjectile);
	this->entity.push_back(portalProjectile);
	this->colEntity.push_back(portalProjectile);
	return *portalProjectile;
}

void EntityManager::handleUpdate(Entity* entity)
{
	PortalProjectile* portalProj = dynamic_cast<PortalProjectile*>(entity);

	if(portalProj != nullptr)
	{
		if(portalProj->collision != DynamicEntity::Collision::NON)
		{
			Vector2D direction;
			switch(portalProj->getCollisionDirection())
			{
				case DynamicEntity::UP: direction.y = 1; break;

				case DynamicEntity::DOWN: direction.y = -1; break;

				case DynamicEntity::LEFT: direction.x = 1; break;

				case DynamicEntity::RIGHT: direction.x = -1; break;
			}

			portal[portalProj->getType()]->reposition( portalProj->getRect().pos, direction );

			Rect& portalRect = portal[portalProj->getType()]->getRect();
			float dim = std::min(portalRect.size.x, portalRect.size.y);
			portalRect.size = portalProj->collision == DynamicEntity::Collision::HORIZONTAL ? Vector2D(dim, dim*2) : Vector2D(dim*2, dim);
			*resize = true;

			portalProj->kill();
		}
	}
}

void EntityManager::eraseDeadEntities()
{
	for(int i = 0; i < colEntity.size(); i++)
	{
		if(!colEntity[i]->isAlive()) colEntity.erase(colEntity.begin() + i);
	}

	for(int i = 0; i < entity.size(); i++)
	{
		if(!entity[i]->isAlive()) entity.erase(entity.begin() + i);
	}
}

bool EntityManager::hasPortalProjectile(Portal::Type type)
{
	if(!portalProj[type]) return false;

	else return portalProj[type]->isAlive();
}
