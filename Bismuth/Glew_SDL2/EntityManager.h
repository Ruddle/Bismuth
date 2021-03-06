#pragma once

#include <vector>
#include "Entity.h"
#include "Entity2D.h"
#include "GraphicComponent.h"
#include "StateComponent.h"
#include "InteractionManager.h"
#include "PhysicComponent.h"
#include "Mesh.h"
#include "Light.h"
#include "World.h"


struct EntityToDelete
{
	int id;
	double timeOfDeath;
};

class EntityManager
{

public:

	EntityManager();
	~EntityManager();

	void update(float time_s);
	void collision();
	void singleCollisionResponse(float time_s);
	void systemCollisionResponse(float time_s);
	void doResponseCollision();

	void add(Entity* entity);
	void add(Entity* parent, Entity *entity);
	void add(Entity2D* entity);
	void suppr(unsigned int id);
	void suppr2D(unsigned int id);
	std::vector<Entity*> getEntities() { return mEntity; }
	std::vector<Entity2D*> getEntities2D() { return mEntity2D; }

	void setTimeOfDeath(int id, double offset);

	InteractionManager* getIM() { return mIM; }

	World* getWorld() { return mWorld; }

private:

	World* mWorld;

	std::vector<Entity*> mEntity;
	std::set<unsigned int> mFreeIds;

	std::vector<Entity2D*> mEntity2D;
	std::set<unsigned int> mFreeIds2D;

	InteractionManager* mIM;

	double mTimeSinceStart_s ;
	std::vector<EntityToDelete> mEntityToDelete;

};
