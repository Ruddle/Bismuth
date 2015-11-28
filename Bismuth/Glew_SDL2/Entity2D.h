#pragma once
#include "GraphicComponent.h"
#include "PhysicComponent2D.h"
class Entity2D
{
public:
	Entity2D();
	Entity2D(GraphicComponent* graphicComponent, PhysicComponent2D* physicComponent);
	~Entity2D();

	PhysicComponent2D*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent* getGraphicComponent(void) { return mGraphicComponent; }

	void setId(int id) { mId = id; }
	int getId() { return mId; }


private:
	GraphicComponent*  mGraphicComponent;
	PhysicComponent2D* mPhysicComponent;
	int mId;
};

