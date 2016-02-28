#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"
#include "Entity.h"

class Mesh : public Entity
{
public:
	Mesh();
	Mesh(GraphicComponent* graphicComponent, PhysicComponent* physicComponent);
	~Mesh();

	Type getType() const {return Entity::MESH;}

	void setPhysicComponent(PhysicComponent* p) { mPhysicComponent = p; }
	void setGraphicComponent(GraphicComponent* p) { mGraphicComponent = p; }

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void)  { return mGraphicComponent; }


private:
	GraphicComponent* mGraphicComponent;
	PhysicComponent* mPhysicComponent;
};
