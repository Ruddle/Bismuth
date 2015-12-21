
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
	glm::vec3 r1;
	glm::vec3 r2;
	PhysicComponent* who1;
	PhysicComponent* who2;
};