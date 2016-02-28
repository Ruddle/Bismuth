#include "Gravity.h"





Gravity::Gravity(PhysicComponent* physicComponent) : Forcefield(physicComponent)
{
}

Gravity::~Gravity()
{
}

glm::vec3 Gravity::force(glm::vec3 pos) const
{
	return glm::vec3(0,0,-9.8);
}
