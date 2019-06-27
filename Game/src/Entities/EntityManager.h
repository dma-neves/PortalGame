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

	Player& getPlayer() { return *player; }
	std::vector<Entity*>& getEntities() { return entities; }
	std::vector<Entity*>& getColEntities() { return colEntities; }
	Portal& getPortal(Portal::Type type) { return *portals[type]; }
	Array<Portal*, 2>& getPortals() { return portals; }
	PortalProjectile& getPortalProjectile(Portal::Type type) { return *portalProj[type]; }
	std::vector<DisplaceableEntity*>& getDisplaceableEntities() { return displaceableEntities; }

	bool hasPortalProjectile(Portal::Type type);

private:
	void eraseDeadEntities();

	void addEntity(Entity* entity);

private:
	std::vector<std::unique_ptr<Entity>> entities_uptr;

	std::vector<Entity*> entities;
	std::vector<Entity*> colEntities; //Colliadable entity
	std::vector<DisplaceableEntity*> displaceableEntities;
	Player* player;
	Array<Portal*, 2> portals;
	Array<PortalProjectile*, 2> portalProj;

	bool* resize;
};

#endif
