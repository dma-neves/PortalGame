#ifndef PORTAL
#define PORTAL

#include "Entity.h"

class Portal : public Entity
{
public:
    enum Type {RED = 0, BLUE};

    Portal(Rect rect, std::string fileName, std::string texturePack, Type type);
    Portal(Rect rect, Type type);

    Type getType() { return type; }

private:
    Type type;
};

#endif
