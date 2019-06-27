#include "EntityManager.h"

EntityManager::EntityManager(bool* resize) : resize(resize)
{
}

void EntityManager::reset()
{
	entities.clear();
	colEntities.clear();
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
	this->colEntities.push_back(player);
	this->displaceableEntities.push_back(player);
	return *player;
}

Portal& EntityManager::addPortal(Portal* portal)
{
	this->portals[portal->getType()].reset(portal);
	this->entities.push_back(portal);
	this->colEntities.push_back(portal);
	return *portal;
}

StaticBlock& EntityManager::addStaticBlock(StaticBlock* staticBlock)
{
	std::unique_ptr<StaticBlock> uptr(staticBlock);
	this->staticBlocks.push_back(std::move(uptr));

	this->entities.push_back(staticBlock);
	this->colEntities.push_back(staticBlock);
	return *staticBlock;
}

DynamicBlock& EntityManager::addDynamicBlock(DynamicBlock* dynamicBlock)
{
	std::unique_ptr<DynamicBlock> uptr(dynamicBlock);
	this->dynamicBlocks.push_back(std::move(uptr));

	this->entities.push_back(dynamicBlock);
	this->colEntities.push_back(dynamicBlock);
	this->displaceableEntities.push_back(dynamicBlock);
	return *dynamicBlock;
}

PortalProjectile& EntityManager::addPortalProjectile(PortalProjectile* portalProjectile)
{
	this->portalProj[portalProjectile->getType()].reset(portalProjectile);
	this->entities.push_back(portalProjectile);
	this->colEntities.push_back(portalProjectile);
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

	for(int i = 0; i < colEntities.size(); i++)
	{
		if(!colEntities[i]->isAlive()) colEntities.erase(colEntities.begin() + i);
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
