#include "DynamicBlock.h"
#include "Player.h"

DynamicBlock::DynamicBlock(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity) :
DynamicEntity(rect, fileName, texturePack, colEntity)
{
}