#pragma once
#include "Mesh.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"
#include "Updatable.h"


class Cube : public Mesh, public Updatable
{
public:
	Cube(EntityManager* em, ResourcesManager* rm, glm::vec3 position, glm::vec3 speed);
	~Cube();

	void update(float time_s);

};

