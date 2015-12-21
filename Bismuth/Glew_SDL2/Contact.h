
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
	glm::vec3 posDiff2;
	glm::vec3 posDiff;
	glm::vec3 rotDiff;
};