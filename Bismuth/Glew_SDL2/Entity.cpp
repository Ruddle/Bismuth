#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	for (int i = 0; i < mChildren.size(); i++)
		delete mChildren[i];

	mParent->suppr(this);
}

void Entity::suppr(Entity * entity)
{
	for (int i = 0; i < mChildren.size();i++)
	{
		if (mChildren[i]->getId() == entity->getId())
		{
			mChildren.erase( mChildren.begin() +   i);
			i = i + mChildren.size();
		}


	}


}





