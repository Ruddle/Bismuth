#include "PhysicBoom.h"


using namespace glm;
PhysicBoom::PhysicBoom(PhysicComponent* physicComponent) : Forcefield(physicComponent)
{
}


PhysicBoom::~PhysicBoom()
{
}



glm::vec3 PhysicBoom::force(glm::vec3 pos) const
{
	vec3 here = vec3(getModel()[3][0], getModel()[3] [1], getModel()[3] [2]);
	return glm::vec3( normalize(pos - here  ) )*600.0f/ length(pos - here) ;
}
