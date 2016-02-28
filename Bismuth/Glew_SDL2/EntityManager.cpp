#include "EntityManager.h"


EntityManager::EntityManager()
{
	mTimeSinceStart_s = 0;
	mIM = new InteractionManager(mEntity);

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

	mWorld = new World();
}
EntityManager::~EntityManager()
{
	for (int i = 0; i < mEntity.size(); i++)
		delete mEntity[i];
}

void EntityManager::update(float time_s)
{
	mTimeSinceStart_s += time_s;
	
	for (int i = 0; i < mEntityToDelete.size(); i++)
	{
		if (mTimeSinceStart_s > mEntityToDelete[i].timeOfDeath)
		{
			suppr(mEntityToDelete[i].id);
			mEntityToDelete.erase(mEntityToDelete.begin() + i);
		}
		
	}




	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		if (entity != nullptr && entity->getType() == Entity::MESH) {

			((Mesh*)entity)->getPhysicComponent()->getStateComponent()->update(time_s);
			entity->setModel(((Mesh*)entity)->getPhysicComponent()->getStateComponent()->getModel());

		}
			
	}
}


void EntityManager::collision()
{
	mIM->collision();
}

void EntityManager::singleCollisionResponse(float time_s)
{
	mIM->singleCollisionResponse(time_s);
}

void EntityManager::systemCollisionResponse(float time_s)
{
	mIM->systemCollisionResponse();
}

void EntityManager::doResponseCollision()
{
	mIM->doResponse();
}


void EntityManager::add(Entity* entity)
{
	if (mFreeIds.size() > 0)
	{
		auto it = mFreeIds.begin();
		mEntity[*it] = entity;
		entity->setId(*it);
		mFreeIds.erase(it);
		mWorld->add(entity);

		entity->setParent(mWorld);
	}
}

void EntityManager::add(Entity* parent, Entity *entity)
{
    if (mFreeIds.size() > 0)
	{
		auto it = mFreeIds.begin();
		mEntity[*it] = entity;
		entity->setId(*it);
		mFreeIds.erase(it);
		parent->add(entity);

		entity->setParent(parent);
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

		for (int i = 0; i < mEntity[id]->getChildren().size(); i++)
			suppr(mEntity[id]->getChildren()[i]->getId());

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

void EntityManager::setTimeOfDeath(int id, double offset_s)
{
	mEntityToDelete.push_back({ id, mTimeSinceStart_s + offset_s });
}
