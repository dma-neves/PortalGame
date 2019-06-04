#ifndef ENTITY_RENDERER
#define ENTITY_RENDERER

#include <vector>
#include <iostream>

#include "Entity.h"

class EntityRenderer
{
public:
	EntityRenderer(Rect camera, Vector2D wSize, std::vector<Entity*>* entity);

	void resizeCamera(Vector2D resizer, Vector2D wSize, bool scaleEntities);
	void scaleEntities() { for(Entity* e : *entity) e->scale(scalar); }

	void update(float dt) {}
	void render(sf::RenderWindow& window);
	void updateViewableEntities();

	Vector2D getWorldPosition(Vector2D pos, sf::RenderWindow& window) 
	{ 
		return ( pos - Vector2D(window.getSize())*0.5f ) / scalar + camera.pos;
	}

private:
	Rect camera;
	float scalar;

	std::vector<Entity*>* entity;
	std::vector<Entity*> viewEntity; //Viewable entity
};

#endif
