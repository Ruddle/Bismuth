#pragma once
#include "Entity.h"
class World : public Entity
{
public:
	World();
	~World();

	Type getType() { return Entity::WORLD; }

};

