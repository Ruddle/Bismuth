#pragma once
#include "Forcefield.h"
class PhysicBoom : public Forcefield
{
public:
	PhysicBoom(PhysicComponent* physicComponent);
	~PhysicBoom();


	glm::vec3 force(glm::vec3 pos) const;
};

