#include "Portal.h"

Portal::Portal(Rect rect, std::string fileName, std::string texturePack, Type type) : Entity(rect, fileName, texturePack), type(type)
{
}

Portal::Portal(Rect rect, Type type) : Entity(rect), type(type)
{
}
