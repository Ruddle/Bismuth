#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Entity
{
public:

    enum Type { MESH, LIGHT, WORLD, };

	Entity();
	~Entity();

	virtual Type getType() const = 0;
	void setId(int id) {mId = id;}
	int getId() {return mId;}
	void add(Entity *entity) { mChildren.push_back(entity); }
	void suppr(Entity *entity);

	std::vector<Entity*>& getChildren() { return mChildren; }

	glm::mat4 getModel() { return mModel; }
	glm::mat4 getLastModel() { return mLastModel; }

	void setModel(glm::mat4 model) { mLastModel = mModel; mModel = model; }
	void setParent(Entity* parent) { mParent = parent; }
	Entity* getParent() { return mParent; }

private:
    int mId;
	glm::mat4 mModel;
	glm::mat4 mLastModel;
	std::vector<Entity*> mChildren;
	Entity* mParent;
};
