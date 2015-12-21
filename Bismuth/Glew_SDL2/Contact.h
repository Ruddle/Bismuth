
#pragma once
#include "glm.hpp"


class PhysicComponent;

struct Contact
{
	glm::vec3 position;
	glm::vec3 normal;
	PhysicComponent* who1;
	PhysicComponent* who2;
};

struct ContactResponse
{
	glm::vec3 normal;
	float jr;
	PhysicComponent* who1;
	PhysicComponent* who2;
};