#include "EntityManager.h"


EntityManager::EntityManager()
{

}
EntityManager::~EntityManager()
{

}

void EntityManager::draw(Camera* camera)
{
	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		entity->getGraphicComponent()->draw(camera);
	}
}

void EntityManager::update()
{
	// Calcul du temps ecoulé depuis l'ancien appel 
	int time = 10; // TODO

	for (int i = 0; i < mEntity.size(); i++)
	{
		Entity *entity = mEntity[i];
		entity->getPhysicComponent()->getStateComponent()->update(time);
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


void EntityManager::add(Entity* entity)
{
	mEntity.push_back(entity);
}
