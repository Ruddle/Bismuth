#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Entity
{
public:

    enum Type { MESH, LIGHT };

	Entity();
	virtual Type getType() const = 0;

private:
	glm::mat4 mModel;
};
