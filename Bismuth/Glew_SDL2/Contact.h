#pragma once


#include "Screw.h"
class PhysicComponent;

struct Contact
{
	glm::vec3 position;
	glm::vec3 normal;
	PhysicComponent* who1;
	PhysicComponent* who2;
};

struct ContactEntity
{
    Contact *contact;
    Entity *ent1;
    Entity *ent2;
};

struct ContactResponse
{
	glm::vec3 normal;
	Screw screw1;
	Screw screw2;
	PhysicComponent* who1;
	PhysicComponent* who2;
};
