#include "EntityManager.h"


EntityManager::EntityManager()
{

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
	mIM->singleCollisionResponse();
	
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