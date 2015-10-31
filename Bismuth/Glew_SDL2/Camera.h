#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"

class Camera
{
public:
	Camera(glm::mat4 &projection);
	~Camera();
	glm::mat4 getProjection() { return mProjection; }
	glm::mat4 getView() { return mView; }

	
private:

	glm::mat4 mProjection;
	glm::mat4 mView;

};
