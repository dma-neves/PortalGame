#include <fstream>

#include <Game.h>

bool validLevel(std::string levelName);

int main()
{
	std::cout << "Window width=height: ";
	int height;
	std::cin >> height;

	std::cout << "Level name: ";
	std::string levelName;
	std::cin >> levelName;
	std::string levelFile = levelName +  ".txt";

	if(!validLevel(levelName)) std::cout << "Error: Invalid level name" << std::endl;

	else
	{
		Game game(Vector2D(height, height), "Portal Game", levelFile);
		game.run();
	}
}

bool validLevel(std::string levelName)
{
	std::ifstream namesFile(LEVEL_NAMES_PATH);

    std::string name;
    while (namesFile >> name)
	{
		if(name == levelName) 
		{
			namesFile.close();
			return true;
		}
	}

    namesFile.close();
	return false;
}
