#ifndef DYNAMIC_BLOCK
#define DYNAMIC_BLOCK

#include "DynamicEntity.h"

class DynamicBlock : public DynamicEntity
{
public:
	DynamicBlock(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity);
	DynamicBlock(Rect rect, std::vector<Entity*>* colEntity);
};

#endif