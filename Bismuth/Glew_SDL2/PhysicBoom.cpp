#include "PhysicBoom.h"



PhysicBoom::PhysicBoom(PhysicComponent* physicComponent) : Forcefield(physicComponent)
{
}


PhysicBoom::~PhysicBoom()
{
}



glm::vec3 PhysicBoom::force(glm::vec3 pos) const
{
	return glm::vec3( normalize(pos)*100.0f/ length(pos) );
}
