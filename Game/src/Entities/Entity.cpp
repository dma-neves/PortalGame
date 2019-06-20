#include "Entity.h"

Entity::Entity(Rect rect, std::string fileName, std::string texturePack) : rect(rect)
{
	texture = TextureManager::loadTexture(TEXTURE_DIR + texturePack + fileName);
}

void Entity::render(sf::RenderWindow& window, Vector2D drawPos)
{
	rectShape.setPosition(drawPos.sfVector());
	window.draw(rectShape);
}

void Entity::scale(float scalar)
{
	rectShape.setSize((rect.size * scalar).sfVector());
	rectShape.setTexture(&texture);
}
