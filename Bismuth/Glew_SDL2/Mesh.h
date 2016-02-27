#pragma once

#include "GraphicComponent.h"
#include "PhysicComponent.h"

class Mesh : public Entity
{
public:
	Mesh();
	Mesh(GraphicComponent* graphicComponent, PhysicComponent* physicComponent);
	~Mesh();

	PhysicComponent*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void)  { return mGraphicComponent; }

	void setId(int id) {mId = id;}
	int getId() { return mId; }

private:
	GraphicComponent* mGraphicComponent;
	PhysicComponent* mPhysicComponent;
	int mId;
};
