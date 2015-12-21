#include "InteractionManager.h"
#include "DetectionProcessor.h"

InteractionManager::InteractionManager(std::vector<Entity*> &entities) : mEntities(entities)
{
}

InteractionManager::~InteractionManager()
{
}

void InteractionManager::collision()
{
	for (auto it = mContacts.begin(); it != mContacts.end(); it++)
		delete (*it);

	mContacts.clear();

	for (int i = 0; i < mEntities.size() - 1; i++)
	{
		Entity *entity_i = mEntities[i];
		if (entity_i != nullptr)
		{
			for (int j = i + 1; j < mEntities.size(); j++)
			{
				Entity *entity_j = mEntities[j];
				if (entity_j != nullptr)
				{
					PhysicComponent *phyI = entity_i->getPhysicComponent(), *phyJ = entity_j->getPhysicComponent();
					Contact* contact = DetectionProcessor::detection(phyI->getDetectionComponent(), phyJ->getDetectionComponent(),
						phyI->getStateComponent()->getPosition(), phyI->getStateComponent()->getRotation(),
						phyJ->getStateComponent()->getPosition(), phyJ->getStateComponent()->getRotation());
					if (contact != nullptr)
						mContacts.push_back(contact);
				}

			}
		}
	}
}

void InteractionManager::singleCollisionResponse()
{
}

void InteractionManager::systemCollisionResponse()
{
}
