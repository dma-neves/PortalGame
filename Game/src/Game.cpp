#include "Game.h"

Game::Game(Vector2D wSize, std::string title) :
window(sf::VideoMode(wSize.x, wSize.y), title),
entityMng(),
entityRen(Rect(Vector2D(20,5), Vector2D(50, 50)), wSize, &entityMng.getEntities()),
levelLoader(&entityMng)
{
	levelLoader.loadLevel("level_1.txt");

	entityMng.addPortal(new Portal(Rect(Vector2D(0,0), Vector2D(1, 1)), "bluePortal.png", levelLoader.getPack(), Portal::BLUE));
	entityMng.addPortal(new Portal(Rect(Vector2D(20,0), Vector2D(1, 1)), "redPortal.png", levelLoader.getPack(), Portal::RED));

	entityRen.resizeCamera(Vector2D(), wSize, true);
}

void Game::run()
{
	while(isRunning)
	{
		float dt = clock.restart().asSeconds() * 3;

		handleEvents(dt);
		update(dt);

		window.clear(sf::Color(2, 3, 43));
		render();
		window.display();
	}
}

void Game::handleEvents(float dt)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			isRunning = false;
			window.close();
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		isRunning = false;
		window.close();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))     entityMng.getPlayer().moveRight(); 
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) entityMng.getPlayer().moveLeft();
	else entityMng.getPlayer().stop();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) entityMng.getPlayer().jump();

	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) lMouseRel = true;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Right)) rMouseRel = true;

	if(lMouseRel && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lMouseRel = false;
		Vector2D mousePos(sf::Mouse::getPosition(window));
		shootPortal(mousePos, Portal::BLUE);
	}
	if(rMouseRel && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rMouseRel = false;
		Vector2D mousePos(sf::Mouse::getPosition(window));
		shootPortal(mousePos, Portal::RED);
	}
}

void Game::update(float dt)
{
	entityMng.update(dt);
}

void Game::render()
{
	entityRen.render(window);
}

void Game::shootPortal(Vector2D mousePos, Portal::Type type)
{
	if(!entityMng.hasPortalProjectile(type))
	{
		Rect rect = entityMng.getPlayer().getRect();
		Vector2D direction = entityRen.getWorldPosition(mousePos, window) - rect.pos;
		direction.setMagnitude( sqrt( pow(rect.size.x, 2) + pow(rect.size.y, 2) ) );
		rect.size = Vector2D(1,1);
		rect.pos += direction;
		entityMng.addPortalProjectile( new PortalProjectile(rect, "", "", &entityMng.getColEntities(), type) );
		entityMng.getPortalProjectile(type).shoot(direction);
		entityRen.resizeCamera(Vector2D(), window.getSize(), true);
	}
}
