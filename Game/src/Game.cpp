#include "Game.h"

Game::Game(Vector2D wSize, std::string title, std::string levelFile) :
window(sf::VideoMode(wSize.x, wSize.y), title, sf::Style::Close),
entityMng(&resize),
entityRen(Rect(Vector2D(20,5), Vector2D(50, 50)), wSize, &entityMng.getEntities(), &resize),
levelLoader(&entityMng)
{
	levelLoader.loadLevel(levelFile);

	entityMng.addPortal(new Portal(Rect(Vector2D(), Vector2D(1, 1)), "bluePortal.png", levelLoader.getPack(), Portal::BLUE));
	entityMng.addPortal(new Portal(Rect(Vector2D(), Vector2D(1, 1)), "redPortal.png", levelLoader.getPack(), Portal::RED));
}

void Game::run()
{
	while(isRunning)
	{
		float dt = clock.restart().asSeconds() * DT_MULTIPLIER;

		for(int i = 0; i < dt; i++)
		{
			float pdt = i == 0 ? (dt - (int)dt) : 1;

			handleEvents(pdt);
			update(pdt);

			window.clear(sf::Color(CLEAR_COLOR));
			render();
			window.display();
		}
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

	if(window.hasFocus())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isRunning = false;
			window.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))     entityMng.getPlayer().moveRight(); 
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) entityMng.getPlayer().moveLeft();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) entityMng.getPlayer().jump();

		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) lMouseRel = true;
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Right)) rMouseRel = true;

		Vector2D mousePos(sf::Mouse::getPosition(window));

		if(lMouseRel && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			lMouseRel = false;
			shootPortal(mousePos, Portal::BLUE);
		}
		if(rMouseRel && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			rMouseRel = false;
			shootPortal(mousePos, Portal::RED);
		}
	}
}

void Game::shootPortal(Vector2D mousePos, Portal::Type type)
{
	if(!entityMng.hasPortalProjectile(type))
	{
		Rect rect = entityMng.getPlayer().getRect();
		Vector2D direction = entityRen.getWorldPosition(mousePos, window) - rect.pos;
		direction.setMagnitude(rect.diagonalLength());
		rect.size = Vector2D(1,1);
		rect.pos += direction;

		bool valid = true;
		for(Entity* e : entityMng.getColEntities())
		{
			if(e->getRect().intersects(rect)) 
			{
				valid = false;
				break;
			}
		}

		if(valid)
		{
			std::string textureFile = type == Portal::Type::BLUE ? "bluePortal.png" : "redPortal.png";
			PortalProjectile& portalProj = entityMng.addPortalProjectile( new PortalProjectile(rect, textureFile, 
			levelLoader.getPack(), type, &entityMng.getColEntities(), &entityMng.getPortals(), &resize) );
			portalProj.shoot(direction);
			resize = true;
		}
	}
}
