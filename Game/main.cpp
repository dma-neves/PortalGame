#include <Game.h>

int main()
{
	std::cout << "Window width=height: ";
	int height;
	std::cin >> height;

	std::cout << "Level name: ";
	std::string levelFile;
	std::cin >> levelFile;
	levelFile += ".txt";

	Game game(Vector2D(height, height), "Portal Game", levelFile);
	game.run();
}
