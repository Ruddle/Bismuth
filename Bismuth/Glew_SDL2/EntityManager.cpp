#include "EntityManager.h"


EntityManager::EntityManager()
{
	mEntity.reserve(1000);

	for (int i = 0; i < 1000; i++)
	{
		mEntity.push_back(nullptr);
		mFreeIds.insert(i);
	}

	mEntity2D.reserve(1000);

	for (int i = 0; i < 1000; i++)
	{
		mEntity2D.push_back(nullptr);
		mFreeIds2D.insert(i);
	}
}
EntityManager::~EntityManager()
{
	for (int i = 0; i < mEntity.size(); i++)
		delete mEntity[i];
}

void EntityManager::update(float time_s)
{

	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		if(entity != nullptr)
			entity->getPhysicComponent()->getStateComponent()->update(time_s);
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

void EntityManager::collisionResponse(float time_s)
{
	for (int i = 0; i < mEntity.size(); i++)
	{
		if(mEntity[i])
			mEntity[i]->getPhysicComponent()->collisionResponse(time_s);
	}
}


void EntityManager::add(Entity* entity)
{
	if (mFreeIds.size() > 0)
	{
		auto it = mFreeIds.begin();
		mEntity[*it] = entity;
		entity->setId(*it);
		mFreeIds.erase(it);
	}
}

void EntityManager::add(Entity2D* entity)
{
	if (mFreeIds.size() > 0)
	{
		auto it = mFreeIds2D.begin();
		mEntity2D[*it] = entity;
		entity->setId(*it);
		mFreeIds2D.erase(it);
	}
}

void EntityManager::suppr(unsigned int id)
{
	if (mEntity[id] != nullptr)
	{
		delete mEntity[id];
		mEntity[id] = nullptr;
		mFreeIds.insert(id);
	}
}

void EntityManager::suppr2D(unsigned int id)
{
	if (mEntity2D[id] != nullptr)
	{
		delete mEntity2D[id];
		mEntity2D[id] = nullptr;
		mFreeIds2D.insert(id);
	}
}