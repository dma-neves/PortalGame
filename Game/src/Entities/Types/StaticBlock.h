#ifndef STATIC_BLOCK
#define STATIC_BLOCK

#include "Entity.h"

class StaticBlock : public Entity
{
public:
    StaticBlock(Rect rect, std::string fileName, std::string texturePack) :
    Entity(rect, fileName, texturePack) {}

    virtual bool isFinishBlock() { return false; }
};

#endif