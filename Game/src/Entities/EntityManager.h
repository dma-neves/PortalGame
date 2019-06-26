#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include <memory>

#include "Player.h"
#include "Portal.h"
#include "PortalProjectile.h"
#include "StaticBlock.h"
#include "DynamicBlock.h"
#include "VectorOp.h"
#include "Array.h"

class EntityManager
{
public:
	EntityManager(bool* resize);

	void reset();
	void update(float dt);

	Player& addPlayer(Player* player);
	Portal& addPortal(Portal* portal);
	StaticBlock& addStaticBlock(StaticBlock* staticBlock);
	DynamicBlock& addDynamicBlock(DynamicBlock* dynamicBlock);
	PortalProjectile& addPortalProjectile(PortalProjectile* portalProjectile);

	Player& getPlayer() { return *player.get(); }
	std::vector<Entity*>& getEntities() { return entities; }
	std::vector<Entity*>& getDynamicEntities() { return dynamicEntities; }
	Portal& getPortal(Portal::Type type) { return *portals[type].get(); }
	Array<std::unique_ptr<Portal>, 2>& getPortals() { return portals; }
	PortalProjectile& getPortalProjectile(Portal::Type type) { return *portalProj[type].get(); }

	bool hasPortalProjectile(Portal::Type type);

private:
	void eraseDeadEntities();

private:
	std::vector<Entity*> entities;
	std::vector<Entity*> dynamicEntities; //Colliadable entity

	std::vector<std::unique_ptr<StaticBlock>> staticBlocks;
	std::vector<std::unique_ptr<DynamicBlock>> dynamicBlocks;
	std::unique_ptr<Player> player;
	Array<std::unique_ptr<Portal>, 2> portals;
	Array<std::unique_ptr<PortalProjectile>, 2> portalProj;

	bool* resize;
};

#endif
