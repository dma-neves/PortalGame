#ifndef STATIC_BLOCK
#define STATIC_BLOCK

#include "Entity.h"

class StaticBlock : public Entity
{
public:
    StaticBlock(Rect rect, std::string fileName, std::string texturePack, bool levelFinish = false) :
    Entity(rect, fileName, texturePack), finishBlock(finishBlock) {}

    bool isFinishBlock() { return finishBlock; }

private:
    bool finishBlock;
};

#endif