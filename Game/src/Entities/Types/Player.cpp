#include "Player.h"

Player::Player(Rect rect, std::string fileName, std::string texturePack, std::vector<Entity*>* colEntity) :
DynamicEntity(rect, fileName, texturePack, colEntity)
{
}

Player::Player(Rect rect, std::vector<Entity*>* colEntity) : DynamicEntity(rect, colEntity)
{
}
