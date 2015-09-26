#pragma once

#include "glm\glm.hpp"
#include "PhysicComponent.h"

class Camera
{
public:
	Camera(glm::mat4 &projection, PhysicComponent* physicComponent);
	~Camera();

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }

private:
	PhysicComponent* mPhysicComponent;
	glm::mat4 mProjection;
	glm::mat4 mView;

};
