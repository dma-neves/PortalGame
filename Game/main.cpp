#include <Game.h>

int main()
{
	std::cout << "Level name: ";
	std::string levelFile;
	std::cin >> levelFile;
	levelFile += ".txt";
	Game game(Vector2D(600, 600), "Portal Game", levelFile);
	game.run();
}
