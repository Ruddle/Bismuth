#pragma once
#include "Mesh.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"
#include "Updatable.h"


class Hat : public Updatable
{
public:
	Hat(EntityManager* em, ResourcesManager* rm,Entity* parent);
	~Hat();
	Entity *getEntity() { return mMesh; }
	void update(float time_s);

private:
	Mesh *mMesh;
};

