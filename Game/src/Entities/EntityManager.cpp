#include "EntityManager.h"

EntityManager::EntityManager(bool* resize) : resize(resize)
{
}

void EntityManager::reset()
{
	entities.clear();
	dynamicEntities.clear();
	staticBlocks.clear();
	dynamicBlocks.clear();
}

void EntityManager::update(float dt)
{
	for(Entity* e : entities) e->update(dt);

	eraseDeadEntities();
}

Player& EntityManager::addPlayer(Player* player)
{
	this->player.reset(player);
	this->entities.push_back(player);
	this->dynamicEntities.push_back(player);
	return *player;
}

Portal& EntityManager::addPortal(Portal* portal)
{
	this->portals[portal->getType()].reset(portal);
	this->entities.push_back(portal);
	this->dynamicEntities.push_back(portal);
	return *portal;
}

StaticBlock& EntityManager::addStaticBlock(StaticBlock* staticBlocks)
{
	std::unique_ptr<StaticBlock> uptr(staticBlocks);
	this->staticBlocks.push_back(std::move(uptr));

	this->entities.push_back(staticBlocks);
	this->dynamicEntities.push_back(staticBlocks);
	return *staticBlocks;
}

DynamicBlock& EntityManager::addDynamicBlock(DynamicBlock* dynamicBlocks)
{
	std::unique_ptr<DynamicBlock> uptr(dynamicBlocks);
	this->dynamicBlocks.push_back(std::move(uptr));

	this->entities.push_back(dynamicBlocks);
	this->dynamicEntities.push_back(dynamicBlocks);
	return *dynamicBlocks;
}

PortalProjectile& EntityManager::addPortalProjectile(PortalProjectile* portalProjectile)
{
	this->portalProj[portalProjectile->getType()].reset(portalProjectile);
	this->entities.push_back(portalProjectile);
	this->dynamicEntities.push_back(portalProjectile);
	return *portalProjectile;
}

void EntityManager::eraseDeadEntities()
{
	for(int i = 0; i < staticBlocks.size(); i++)
	{
		if(!staticBlocks[i]->isAlive()) staticBlocks.erase(staticBlocks.begin() + i);
	}

	for(int i = 0; i < dynamicBlocks.size(); i++)
	{
		if(!dynamicBlocks[i]->isAlive()) dynamicBlocks.erase(dynamicBlocks.begin() + i);
	}

	for(int i = 0; i < dynamicEntities.size(); i++)
	{
		if(!dynamicEntities[i]->isAlive()) dynamicEntities.erase(dynamicEntities.begin() + i);
	}

	for(int i = 0; i < entities.size(); i++)
	{
		if(!entities[i]->isAlive()) entities.erase(entities.begin() + i);
	}
}

bool EntityManager::hasPortalProjectile(Portal::Type type)
{
	if(!portalProj[type]) return false;

	else return portalProj[type]->isAlive();
}
