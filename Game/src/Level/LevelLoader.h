#ifndef LEVEL_LOADER
#define LEVEL_LOADER

#include <vector>
#include <fstream>

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
	EntityManager* entityMng;
};

#endif