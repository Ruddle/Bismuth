#pragma once
#include "PhysicComponent.h"
#include "glm\glm.hpp"

class PhysicComponent;

struct Contact 
{
	glm::vec3 position;
	glm::vec3 normal;
	PhysicComponent* who;
};

