#pragma once
#include <vector>
#include "Constraint.h"

class PhysicSystem
{
public:
	PhysicSystem();
	void addConstraint(Entity *entityA, Screw linkage, Entity *entityB);
	std::vector<Constraint*> getConstraints(Entity *entity);
	~PhysicSystem();

private:
	std::vector<Constraint*> mConstraints;
};

