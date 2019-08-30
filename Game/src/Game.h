#ifndef GAME
#define GAME

#define DT_MULTIPLIER 3
#define CLEAR_COLOR 2, 3, 43

#include <SFML/Graphics.hpp>
#include <vector>

#include "LevelLoader.h"
#include "EntityManager.h"
#include "EntityRenderer.h"
#include "Player.h"

class Game
{
public:
	Game(Vector2D wSize, std::string title, std::string levelFile);

	void run();
	void handleEvents(float dt);
	void update(float dt);
	void render();

private:
	void addPortals();
	void shootPortal(Vector2D mousePos, Portal::Type type);

private:
	bool isRunning = true;
	std::string levelFile;
	EntityManager entityMng;
	EntityRenderer entityRen;
	LevelLoader levelLoader;

	sf::RenderWindow window;
	sf::Clock clock;
	bool lMouseRel = false;
	bool rMouseRel = false;
	bool resetRel = false;

	bool resize = true;
};

#endif
