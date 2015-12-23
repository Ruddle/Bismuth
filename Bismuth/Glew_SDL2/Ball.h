#pragma once
#include "Entity.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "SphereDetectionComponent.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"
#include "Updatable.h"

class Ball : public Updatable
{
public:
	Ball(EntityManager* em,ResourcesManager* rm, glm::vec3 position, glm::vec3 speed);
	~Ball();
	Entity *getEntity() { return mEntity; }

	void update(float time_s);

private: 
	Entity* mEntity;
};

