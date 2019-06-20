#include "DynamicBlock.h"

DynamicBlock::DynamicBlock(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity) :
DynamicEntity(rect, fileName, texturePack, colEntity)
{
}

DynamicBlock::DynamicBlock(Rect rect, std::vector<Entity*>* colEntity) : DynamicEntity(rect, colEntity)
{
}