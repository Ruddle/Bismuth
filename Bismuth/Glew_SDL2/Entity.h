#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Entity
{
public:
	Entity();
	Entity(GraphicComponent* graphicComponent, PhysicComponent* physicComponent);
	~Entity();

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void)  { return mGraphicComponent; }

	void setId(int id) {mId = id;}
	int getId() { return mId; }

private:
	GraphicComponent* mGraphicComponent;
	PhysicComponent* mPhysicComponent;
	int mId;
};
