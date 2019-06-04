#include "Entity.h"

Entity::Entity(Rect rect, std::string fileName, std::string texturePack) : rect(rect)
{
	setTexture(fileName, texturePack);
}

void Entity::render(sf::RenderWindow& window, Vector2D drawPos)
{
	rectShape.setPosition(drawPos.sfVector());
	rectShape.setTexture(&texture);
	rectShape.setFillColor(sf::Color::White);
	window.draw(rectShape);
}

void Entity::scale(float scalar)
{
	rectShape.setSize((rect.size * scalar).sfVector());
}

void Entity::setTexture(std::string fileName, std::string texturePack)
{
	texture = TextureManager::loadTexture(TEXTURE_DIR + texturePack + fileName);
}
