#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"

class Camera
{
public:
	Camera(glm::mat4 &projection);
	~Camera();

	
private:

	glm::mat4 mProjection;
	glm::mat4 mView;

};
