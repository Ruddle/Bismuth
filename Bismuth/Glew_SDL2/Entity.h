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
	int getId() {return mId;}
	void add(Entity *entity) { mChildren.push_back(entity); }

private:
    int mId;
	glm::mat4 mModel;
	std::vector<Entity*> mChildren;
};
