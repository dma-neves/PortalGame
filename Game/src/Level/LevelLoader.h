#ifndef LEVEL_LOADER
#define LEVEL_LOADER

#include <vector>
#include <fstream>

#include "StaticBlock.h"
#include "DynamicBlock.h"
#include "Player.h"
#include "TextureManager.h"
#include "EntityManager.h"

class LevelLoader
{
public:
	LevelLoader(EntityManager* entityMng);

	void loadLevel(std::string fileName);

	std::string getPack() { return texturePack; }

private:
	std::string texturePack;
	Vector2D size;

	EntityManager* entityMng;
};

#endif