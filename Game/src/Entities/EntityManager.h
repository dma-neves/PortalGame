#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include <memory>

#include "Player.h"
#include "Portal.h"
#include "PortalProjectile.h"
#include "VectorOp.h"
#include "Array.h"

class EntityManager
{
public:
	EntityManager(bool* resize);

	void reset();
	void update(float dt);
	void handleUpdate(Entity* entity);
	void eraseDeadEntities();

	Player& addPlayer(Player* player);
	Portal& addPortal(Portal* portal);
	Entity& addStaticBlock(Entity* staticBlock);
	PortalProjectile& addPortalProjectile(PortalProjectile* portalProjectile);

	Player& getPlayer() { return *player.get(); }
	std::vector<Entity*>& getEntities() { return entity; }
	std::vector<Entity*>& getColEntities() { return colEntity; }
	Portal& getPortal(Portal::Type type) { return *portal[type].get(); }
	Array<std::unique_ptr<Portal>, 2>& getPortals() { return portal; }
	PortalProjectile& getPortalProjectile(Portal::Type type) { return *portalProj[type].get(); }

	bool hasPortalProjectile(Portal::Type type);

private:
	std::vector<Entity*> entity;
	std::vector<Entity*> colEntity; //Colliadable entity

	std::vector<std::unique_ptr<Entity>> staticBlock;
	std::unique_ptr<Player> player;
	Array<std::unique_ptr<Portal>, 2> portal;
	Array<std::unique_ptr<PortalProjectile>, 2> portalProj;

	bool* resize;

	Portal** tempArr;
};

#endif
