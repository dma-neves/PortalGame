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
		Vector2D size;

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
					entityMng->addStaticBlock(new StaticBlock(Rect(Vector2D(x, y), Vector2D(1,1)), 
					"staticBlock.png", texturePack));
					break;

				case 'P':
					entityMng->addPlayer(new Player(Rect(Vector2D(x,y), Vector2D(1,1.8f)), 
					"player.png", texturePack, &entityMng->getColEntities(), &entityMng->getPortals()));
					break;
				case 'O':
					entityMng->addDynamicBlock(new DynamicBlock(Rect(Vector2D(x, y), Vector2D(1,1)), 
					"dynamicBlock.png", texturePack, &entityMng->getColEntities(), &entityMng->getPortals()));
					break;

				case 'F':
					entityMng->addStaticBlock(new StaticBlock(Rect(Vector2D(x-0.5f, y-0.5f), Vector2D(2,2)), 
					"finishBlock.png", texturePack, true));
					break;

				case '+':
					entityMng->addStaticBlock(new StaticBlock(Rect(Vector2D(x, y-0.5f), Vector2D(1,2)), 
					"gate.png", texturePack));
					break;
				}
			}
		}

		int numGates;
		levelFile >> numGates;
		for(int i = 0; i < numGates; i++)
		{
			Vector2D gatePos;
			Vector2D leverPos;

			levelFile >> gatePos.x;
			levelFile >> gatePos.y;
			gatePos.y -= 0.5f;
			levelFile >> leverPos.x;
			levelFile >> leverPos.y;

			StaticBlock& sb = entityMng->addStaticBlock(new Gate(Rect(gatePos, Vector2D(1,2)), "gate.png", texturePack));
			Gate* gate = static_cast<Gate*>(&sb);
			entityMng->addStaticBlock(new Lever(Rect(leverPos, Vector2D(1,1)), "lever.png", texturePack, gate, 
			&entityMng->getDisplaceableEntities()));
		}

		levelFile.close();
	}
}
