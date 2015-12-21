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
	for (int i = 0; i < mEntities.size() - 1; i++)
	{
		Entity *entity_i = mEntities[i];
		if (entity_i != nullptr)
		{
			for (int j = i + 1; j < mEntities.size(); j++)
			{
				Entity *entity_j = mEntities[j];
				if (entity_j != nullptr)
					DetectionProcessor::detection()

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
