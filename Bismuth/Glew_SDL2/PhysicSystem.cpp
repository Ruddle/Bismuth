#include "PhysicSystem.h"



PhysicSystem::PhysicSystem()
{
}

void PhysicSystem::addConstraint(Entity * entityA, Screw linkage, Entity * entityB)
{
	Constraint *constraint = new Constraint;
	constraint->entityA = entityA;
	constraint->entityB = entityB;
	constraint->linkage = linkage;

	mConstraints.push_back(constraint);
}

std::vector<Constraint*> PhysicSystem::getConstraints(Entity * entity)
{
	std::vector<Constraint*> constraints;

	for (auto it = mConstraints.begin(); it != mConstraints.end(); it++)
	{
		if((*it)->entityA == entity || (*it)->entityB == entity)
			constraints.push_back(*it);
	}

	return constraints;
}




PhysicSystem::~PhysicSystem()
{
}
