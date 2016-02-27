#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Entity
{
public:

    enum Type { MESH, LIGHT };

	Entity();
	virtual Type getType() const = 0;
	void setId(int id) {mId = id;}
	void getId() {return mId;}

private:
    int mId;
	glm::mat4 mModel;
};
