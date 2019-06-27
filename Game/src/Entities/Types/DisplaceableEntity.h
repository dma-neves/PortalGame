#ifndef DISPLACEABLE_ENTITY
#define DISPLACEABLE_ENTITY

#include <memory>
#include <array>

#include "Portal.h"
#include "Lever.h"
#include "DynamicEntity.h"
#include "Array.h"

class DisplaceableEntity : public DynamicEntity
{
public:
	DisplaceableEntity(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities,
	Array<Portal*, 2>* portals);

	void handleCollisionEffect(Vector2D updatedPos, float dt, std::vector<std::pair<Entity*, Collision>>& colliders) override;

private:
	Portal* getPortal(Portal::Type type) { return (*portals)[type]; }

	void handlePortalCollisionEffect(std::vector<std::pair<Entity*, Collision>>& colliders);
	void gotoPortal(Portal* originPortal, Portal* destPortal);

private:
	Array<Portal*, 2>* portals;
};

#endif