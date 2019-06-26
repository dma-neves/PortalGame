#ifndef DYNAMIC_BLOCK
#define DYNAMIC_BLOCK

#include "DisplaceableEntity.h"

class DynamicBlock : public DisplaceableEntity
{
public:
	DynamicBlock(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities,
	Array<std::unique_ptr<Portal>, 2>* portals) :
	DisplaceableEntity(rect, fileName, texturePack, colEntities, portals)
	{
	}
};

#endif