#pragma once
#include "GraphicComponent2D.h"
#include "PhysicComponent2D.h"
class Entity2D
{
public:
	Entity2D();
	Entity2D(GraphicComponent2D* graphicComponent, PhysicComponent2D* physicComponent);
	~Entity2D();

	PhysicComponent2D*  getPhysicComponent(void) { return mPhysicComponent; }
	GraphicComponent2D* getGraphicComponent(void) { return mGraphicComponent; }

	void setId(int id) { mId = id; }
	int getId() { return mId; }


private:
	GraphicComponent2D*  mGraphicComponent;
	PhysicComponent2D* mPhysicComponent;
	int mId;
};

