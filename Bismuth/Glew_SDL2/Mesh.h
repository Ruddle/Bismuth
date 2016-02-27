#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Mesh : public Entity
{
public:
	Mesh();
	Mesh(GraphicComponent* graphicComponent, PhysicComponent* physicComponent);
	~Mesh();

	Type getType() const {return Entity::MESH;}

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void)  { return mGraphicComponent; }


private:
	GraphicComponent* mGraphicComponent;
	PhysicComponent* mPhysicComponent;
};
