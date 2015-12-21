#pragma once
#include <vector>
#include "Entity.h"
#include "Contact.h"

class InteractionManager
{
public:
	InteractionManager(std::vector<Entity*> &entities);
	~InteractionManager();
	void collision();
	void singleCollisionResponse();
	void systemCollisionResponse();

private:
	std::vector<Entity*> &mEntities;
	std::vector<Contact*> mContacts;
	std::vector<ContactResponse> mResponses;
};

