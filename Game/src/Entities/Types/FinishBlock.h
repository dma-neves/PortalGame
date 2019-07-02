#ifndef FINISH_BLOCK
#define FINISH_BLOCK

#include "StaticBlock.h"

class FinishBlock : public StaticBlock
{
public:
    FinishBlock(Rect rect, std::string fileName, std::string texturePack) : StaticBlock(rect, fileName, texturePack) {}

    bool isFinishBlock() override { return true; }
    bool reached = false;
};

#endif