#pragma once
#include "Mesh.h"
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
	Mesh *getMesh() { return mMesh; }

	void update(float time_s);

private:
	Mesh *mMesh;
};

