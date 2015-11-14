#pragma once
#include "glm.hpp"


class PhysicComponent;

struct Contact 
{
	glm::vec3 position;
	glm::vec3 normal;
	PhysicComponent* who;
};

