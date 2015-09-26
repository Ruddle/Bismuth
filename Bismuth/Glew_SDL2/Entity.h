#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Entity
{
public:
	Entity(GraphicComponent* graphicComponent, PhysicComponent* physicComponent);
	~Entity();

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void)  { return mGraphicComponent; }

private:
	GraphicComponent* mGraphicComponent;
	PhysicComponent* mPhysicComponent;
};
