#pragma once
#include "Entity.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "SphereDetectionComponent.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"


class Ball
{
public:
	Ball(EntityManager* em,ResourcesManager* rm, glm::vec3 position, glm::vec3 speed);
	~Ball();

	void update(float elapsedTime);

private: 
	Entity* mEntity;
};

