#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(Rect camera, Vector2D wSize, std::vector<Entity*>* entities, bool* resize) :
camera(camera), entities(entities), resize(resize)
{
}

void EntityRenderer::resizeCamera(Vector2D resizer, Vector2D wSize, bool scaleEntities)
{
	camera.size += resizer;
	scalar = wSize.x / camera.size.x;

	if(wSize.y / camera.size.y != scalar)
	{
		std::cout << "Warning: Scalar incongruity while resizing camera ( ";
		std::cout << scalar << " | " << wSize.y/camera.size.y << " )" << std::endl;
	}

	if(scaleEntities) this->scaleEntities();
}

void EntityRenderer::updateViewableEntities()
{
	viewEntities.clear();
	for(Entity* e : *entities)
	{
		if(camera.intersects(e->getRect())) viewEntities.push_back(e);
	}
}

void EntityRenderer::render(sf::RenderWindow& window)
{
	if(resize)
	{
		resizeCamera(Vector2D(), window.getSize(), true);
		*resize = false;
	}

	updateViewableEntities();

	for(Entity* e : viewEntities)
	{
		Vector2D drawPos = (e->getOrigin() - camera.getOrigin()) * scalar;
		e->render(window, drawPos);
	}
}
