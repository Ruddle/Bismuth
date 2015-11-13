#pragma once

#include <vector>
#include "Entity.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include "PhysicComponent.h"

class EntityManager
{

public:

	EntityManager();
	~EntityManager();

	void update(float elapsedTime);
	void collision();
	void collisionResponse(float timestep);

	void add(Entity* entity);
	std::vector<Entity*> getEntities() { return mEntity; }

private:

	std::vector<Entity*> mEntity;
	int nextId;
};