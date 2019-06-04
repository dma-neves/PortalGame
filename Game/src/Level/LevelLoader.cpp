#include "LevelLoader.h"

LevelLoader::LevelLoader(EntityManager* entityMng) : entityMng(entityMng)
{
}

void LevelLoader::loadLevel(std::string fileName)
{
	std::ifstream levelFile;
	levelFile.open(LEVEL_DIR + fileName);

	if(!levelFile.is_open())
	{
		std::cout << "Error: Unable to open level file (" << LEVEL_DIR + fileName;
		std::cout << ") while loading level" << std::endl;
	}

	else
	{
		entityMng->reset();

		levelFile >> texturePack;
		levelFile >> size.x >> size.y;

		for(int y = 0; y < size.y; y++)
		{
			for(int x = 0; x < size.x; x++)
			{
				char tile;
				levelFile >> tile;

				switch(tile)
				{
				case '#':
					entityMng->addStaticBlock(new Entity(Rect(Vector2D(x, y), Vector2D(1,1)), "staticBlock.png", texturePack));
					break;

				case 'P':
					entityMng->addPlayer(new Player(Rect(Vector2D(x,y), Vector2D(1,1.8f)), "player.png", texturePack, &entityMng->getColEntities()));
					break;
				}
			}
		}
		levelFile.close();
	}
}