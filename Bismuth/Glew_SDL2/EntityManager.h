#pragma once

#include <vector>
#include "Entity.h"
#include "Camera.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include "PhysicComponent.h"

class EntityManager
{

public:

	EntityManager();
	~EntityManager();

	void draw(Camera* camera);
	void update();
	void collision();

	void add(Entity* entity);

private:

	std::vector<Entity*> mEntity;
};