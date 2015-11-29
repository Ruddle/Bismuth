#pragma once
#include "Entity.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"
#include "Updatable.h"


class Cube : public Updatable
{
public:
	Cube(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed);
	~Cube();
	Entity *getEntity() { return mEntity; }
	void update(float elapsedTime);

private:
	Entity* mEntity;
};

