#ifndef LEVER
#define LEVER

#define COLLISION_MARGIN 0.2

#include <vector>

#include "Gate.h"

class DisplaceableEntity;

class Lever : public StaticBlock
{
public:

    Lever(Rect rect, std::string fileName, std::string texturePack, Gate* gate, std::vector<DisplaceableEntity*>* displaceableEntities);

    void update(float dt) override;

private:
    Gate* gate;
    std::vector<DisplaceableEntity*>* displaceableEntities;
};

#endif