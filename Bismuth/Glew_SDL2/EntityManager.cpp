#include "EntityManager.h"


EntityManager::EntityManager()
{
	nextId = 1;
}
EntityManager::~EntityManager()
{
	for (int i = 0; i < mEntity.size(); i++)
		delete mEntity[i];
}

void EntityManager::update(float elapsedTime)
{

	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		entity->getPhysicComponent()->getStateComponent()->update(elapsedTime);
	}
}


void EntityManager::collision()
{

	//Effacement des contactes précedent
	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		entity->getPhysicComponent()->clearContact();
	}
	
	//Géneration des nouveaux contactes
	for (int i = 0; i < mEntity.size()-1; i++)
	{
		Entity *entity_i = mEntity[i];
		for (int j = i+1; j < mEntity.size(); j++)
		{
			Entity *entity_j = mEntity[j];

			entity_i->getPhysicComponent()->getCollision(entity_j->getPhysicComponent());

		}
	}
}

void EntityManager::collisionResponse(float timestep)
{
	for (int i = 0; i < mEntity.size(); i++)
	{
		mEntity[i]->getPhysicComponent()->collisionResponse(timestep);
	}
}


void EntityManager::add(Entity* entity)
{
	mEntity.push_back(entity);
	entity->setId(nextId);
	nextId++;
}
