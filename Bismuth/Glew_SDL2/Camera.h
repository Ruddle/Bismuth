#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"

class Camera
{
public:
	Camera(glm::mat4 &projection);
	~Camera();
	glm::mat4 getProjection() const { return mProjection; }
	glm::mat4 getView() const { return mView; }

	
private:

	glm::mat4 mProjection;
	glm::mat4 mView;

};
