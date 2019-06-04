#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(Rect camera, Vector2D wSize, std::vector<Entity*>* entity) :
camera(camera), entity(entity)
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
	viewEntity.clear();
	for(Entity* e : *entity)
	{
		if(camera.intersects(e->getRect())) viewEntity.push_back(e);
	}
}

void EntityRenderer::render(sf::RenderWindow& window)
{
	updateViewableEntities();

	for(Entity* e : viewEntity)
	{
		Vector2D drawPos = (e->getOrigin() - camera.getOrigin()) * scalar;
		e->render(window, drawPos);
	}
}
