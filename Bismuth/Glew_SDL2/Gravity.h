#pragma once
#include "Forcefield.h"
class Gravity : public Forcefield
{
public:
	Gravity(DetectionComponent* detectionComponent);
	~Gravity();

	glm::vec3 force(glm::vec3 pos);
};

