#ifndef ENTITY_RENDERER
#define ENTITY_RENDERER

#include <vector>
#include <iostream>

#include "Entity.h"

#define CAMERA_SPEED 5

class EntityRenderer
{
public:
	enum Direction {LEFT = 0, RIGHT, UP, DOWN};

	EntityRenderer(Rect camera, Vector2D wSize, std::vector<Entity*>* entities, bool* resize);

	void movCamera(Direction dir, float dt);
	void resizeCamera(Vector2D resizer, Vector2D wSize, bool scaleEntities);
	void scaleEntities() { for(Entity* e : *entities) e->scale(scalar); }

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

	std::vector<Entity*>* entities;
	std::vector<Entity*> viewEntities; //Viewable entities
	bool* resize;
};

#endif
