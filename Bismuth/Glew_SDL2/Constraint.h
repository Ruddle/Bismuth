#pragma once

#include "Screw.h"
#include "Entity.h"

struct Constraint
{
	Entity *entityA;
	Screw linkage;
	Entity *entityB;
};
