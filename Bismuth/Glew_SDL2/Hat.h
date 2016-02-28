#pragma once
#include "Mesh.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "PhysicComponent.h"
#include "ResourcesManager.h"
#include "CubeDetectionComponent.h"
#include "EntityManager.h"
#include "Updatable.h"


class Hat : public Mesh, public Updatable
{
public:
	Hat(EntityManager* em, ResourcesManager* rm,Entity* parent);
	~Hat();

	void update(float time_s);

};

