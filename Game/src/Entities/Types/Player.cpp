#include "Player.h"

Player::Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntities,
Array<Portal*, 2>* portals) :
DisplaceableEntity(rect, fileName, texturePack, colEntities, portals)
{
}