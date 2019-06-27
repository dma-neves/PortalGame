#include <Game.h>

int main()
{
	std::cout << "Level file: ";
	std::string levelFile;
	std::cin >> levelFile;
	Game game(Vector2D(600, 600), "Portal Game", levelFile);
	game.run();
}
