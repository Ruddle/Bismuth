#include "Gravity.h"





Gravity::Gravity(DetectionComponent * detectionComponent) : Forcefield(detectionComponent)
{
}

Gravity::~Gravity()
{
}

glm::vec3 Gravity::force(glm::vec3 pos)
{
	return glm::vec3(0,0,-9.8);
}
