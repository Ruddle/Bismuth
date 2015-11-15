#pragma once
#include "Entity.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"


class Cube
{
public:
	Cube(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed);
	~Cube();

	void update(float elapsedTime);

private:
	Entity* mEntity;
};

