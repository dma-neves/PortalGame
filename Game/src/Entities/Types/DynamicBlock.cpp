#include "DynamicBlock.h"
#include "Player.h"

DynamicBlock::DynamicBlock(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* dynamicEntities) :
DynamicEntity(rect, fileName, texturePack, dynamicEntities)
{
}