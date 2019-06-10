#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include <memory>

#include "Player.h"
#include "Portal.h"
#include "PortalProjectile.h"
#include "VectorOp.h"

class EntityManager
{
public:
	EntityManager();

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
	PortalProjectile& getPortalProjectile(Portal::Type type) { return *portalProj[type].get(); }

	bool hasPortalProjectile(Portal::Type type);

private:
	std::vector<Entity*> entity;
	std::vector<Entity*> colEntity; //Colliadable entity

	std::vector<std::unique_ptr<Entity>> staticBlock;
	std::unique_ptr<Player> player;
	std::unique_ptr<Portal> portal[2];
	std::unique_ptr<PortalProjectile> portalProj[2];
};

#endif
