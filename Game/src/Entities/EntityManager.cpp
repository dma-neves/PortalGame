#include "EntityManager.h"

EntityManager::EntityManager(bool* resize) : resize(resize)
{
}

void EntityManager::addEntity(Entity* entity)
{
	std::unique_ptr<Entity> uptr(entity);
	entities_uptr.push_back(std::move(uptr));
	entities.push_back(entity);
}

void EntityManager::reset()
{
	entities.clear();
	colEntities.clear();
	displaceableEntities.clear();
	entities_uptr.clear();

	player = nullptr;
	finishBlock = nullptr;
	portals.reset();
	portalProj.reset();
}

void EntityManager::update(float dt)
{
	for(Entity* e : entities) e->update(dt);

	eraseDeadEntities();
}

Player& EntityManager::addPlayer(Player* player)
{
	addEntity(player);

	this->player = player;
	colEntities.push_back(player);
	displaceableEntities.push_back(player);
	return *player;
}

Portal& EntityManager::addPortal(Portal* portal)
{
	addEntity(portal);

	portals[portal->getType()] = portal;
	colEntities.push_back(portal);
	return *portal;
}

StaticBlock& EntityManager::addStaticBlock(StaticBlock* staticBlock)
{
	addEntity(staticBlock);

	colEntities.push_back(staticBlock);
	return *staticBlock;
}

DynamicBlock& EntityManager::addDynamicBlock(DynamicBlock* dynamicBlock)
{
	addEntity(dynamicBlock);

	colEntities.push_back(dynamicBlock);
	displaceableEntities.push_back(dynamicBlock);
	return *dynamicBlock;
}

PortalProjectile& EntityManager::addPortalProjectile(PortalProjectile* portalProjectile)
{
	addEntity(portalProjectile);

	portalProj[portalProjectile->getType()] =portalProjectile;
	colEntities.push_back(portalProjectile);
	return *portalProjectile;
}

FinishBlock& EntityManager::addFinishBlock(FinishBlock* finishBlock)
{
	addEntity(finishBlock);

	this->finishBlock = finishBlock;
	colEntities.push_back(finishBlock);
	return *finishBlock;
}

void EntityManager::eraseDeadEntities()
{
	for(int i = 0; i < entities_uptr.size(); i++)
	{
		if(!entities_uptr[i].get()->isAlive()) entities_uptr.erase(entities_uptr.begin() + i);
	}

	for(int i = 0; i < entities.size(); i++)
	{
		if(!entities[i]->isAlive()) entities.erase(entities.begin() + i);
	}

	for(int i = 0; i < displaceableEntities.size(); i++)
	{
		if(!displaceableEntities[i]->isAlive()) displaceableEntities.erase(displaceableEntities.begin() + i);
	}

	for(int i = 0; i < colEntities.size(); i++)
	{
		if(!colEntities[i]->isAlive()) colEntities.erase(colEntities.begin() + i);
	}
}

bool EntityManager::hasPortalProjectile(Portal::Type type)
{
	if(!portalProj[type]) return false;

	else return portalProj[type]->isAlive();
}
