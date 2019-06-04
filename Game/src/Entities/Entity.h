#ifndef ENTITY
#define ENTITY

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Rect.h"
#include "TextureManager.h"
#include "Directories.h"

class Entity
{
public:
	// @param: Rectangle defining the Entity, Entitys texture file directory
	Entity(Rect rect, std::string fileName, std::string texturePack);
	Entity(Rect rect) : rect(rect) {}

	virtual void update(float dt) {}
	void render(sf::RenderWindow& window, Vector2D drawPos);

	void scale(float scalar);
	void setTexture(std::string fileName, std::string texturePack);

	Vector2D getOrigin() { return rect.getOrigin(); }
	Rect& getRect() { return rect; }

	bool isAlive() { return alive; }
	void kill() { alive = false; }

protected:
	Rect rect;
	sf::RectangleShape rectShape;
	sf::Texture texture;
	
private:
	bool alive = true;
};

#endif
