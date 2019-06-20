#include "EntityManager.h"

EntityManager::EntityManager(bool* resize) : resize(resize)
{
}

void EntityManager::reset()
{
	entity.clear();
	colEntity.clear();
	staticBlock.clear();
	dynamicBlock.clear();
}

void EntityManager::update(float dt)
{
	for(Entity* e : entity) e->update(dt);

	eraseDeadEntities();
}

Player& EntityManager::addPlayer(Player* player)
{
	this->player.reset(player);
	this->entity.push_back(player);
	this->colEntity.push_back(player);
	return *player;
}

Portal& EntityManager::addPortal(Portal* portal)
{
	this->portal[portal->getType()].reset(portal);
	this->entity.push_back(portal);
	this->colEntity.push_back(portal);
	return *portal;
}

StaticBlock& EntityManager::addStaticBlock(StaticBlock* staticBlock)
{
	std::unique_ptr<StaticBlock> uptr(staticBlock);
	this->staticBlock.push_back(std::move(uptr));

	this->entity.push_back(staticBlock);
	this->colEntity.push_back(staticBlock);
	return *staticBlock;
}

DynamicBlock& EntityManager::addDynamicBlock(DynamicBlock* dynamicBlock)
{
	std::unique_ptr<DynamicBlock> uptr(dynamicBlock);
	this->dynamicBlock.push_back(std::move(uptr));

	this->entity.push_back(dynamicBlock);
	this->colEntity.push_back(dynamicBlock);
	return *dynamicBlock;
}

PortalProjectile& EntityManager::addPortalProjectile(PortalProjectile* portalProjectile)
{
	this->portalProj[portalProjectile->getType()].reset(portalProjectile);
	this->entity.push_back(portalProjectile);
	this->colEntity.push_back(portalProjectile);
	return *portalProjectile;
}

void EntityManager::eraseDeadEntities()
{
	for(int i = 0; i < staticBlock.size(); i++)
	{
		if(!staticBlock[i]->isAlive()) staticBlock.erase(staticBlock.begin() + i);
	}

	for(int i = 0; i < dynamicBlock.size(); i++)
	{
		if(!dynamicBlock[i]->isAlive()) dynamicBlock.erase(dynamicBlock.begin() + i);
	}

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
