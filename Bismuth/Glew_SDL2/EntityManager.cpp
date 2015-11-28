#include "EntityManager.h"


EntityManager::EntityManager()
{
	nextId = 1;
	mFreeIds.reserve(1000);
	mEntity.reserve(1000);

	for (int i = 0; i < 1000; i++)
	{
		mFreeIds.push_back(true);
		mEntity.push_back(nullptr);
	}
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
		if(entity != nullptr)
			entity->getPhysicComponent()->getStateComponent()->update(elapsedTime);
	}
}


void EntityManager::collision()
{

	//Effacement des contactes précedent
	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		if (entity != nullptr)
			entity->getPhysicComponent()->clearContact();
	}
	
	//Géneration des nouveaux contactes
	for (int i = 0; i < mEntity.size()-1; i++)
	{
		Entity *entity_i = mEntity[i];
		if (entity_i != nullptr)
		{
			for (int j = i + 1; j < mEntity.size(); j++)
			{
				Entity *entity_j = mEntity[j];
				if(entity_j != nullptr)
					entity_i->getPhysicComponent()->getCollision(entity_j->getPhysicComponent());

			}
		}
	}
}

void EntityManager::collisionResponse(float timestep)
{
	for (int i = 0; i < mEntity.size(); i++)
	{
		if(mEntity[i])
			mEntity[i]->getPhysicComponent()->collisionResponse(timestep);
	}
}


void EntityManager::add(Entity* entity)
{
	for (int i = 0; i < mEntity.size(); i++)
	{
		if (mFreeIds[i])
		{
			mEntity[i] = entity;
			mFreeIds[i] = false;
			entity->setId(i);
			break;
		}
	}
}

void EntityManager::suppr(unsigned int id)
{
	if (mEntity[id] != nullptr)
	{
		delete mEntity[id];
		mEntity[id] = nullptr;
		mFreeIds[id] = true;
	}
}