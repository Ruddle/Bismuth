#pragma once
#include "Entity2D.h"
#include "GraphicComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "EntityManager.h"
#include <string>
class Letter
{
public:
	Letter(EntityManager* em, ResourcesManager* rm, std::string path, char c, glm::vec2 position,glm::vec2 resolution,float scale);
	~Letter();

	Entity2D* getEntity() { return mEntity; }

private:
	char mC;
	Entity2D* mEntity;
};

