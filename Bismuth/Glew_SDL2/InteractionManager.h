#pragma once
#include <vector>
#include "Entity.h"
#include "PhysicComponent.h"
#include "Screw.h"





class InteractionManager
{
public:
	InteractionManager(std::vector<Entity*> &entities);
	~InteractionManager();
	void collision();
	void singleCollisionResponse();
	void systemCollisionResponse();
	void doResponse();

	
private:
	std::vector<Entity*> &mEntities;
	std::vector<Contact*> mContacts;
	std::vector<ContactResponse> mResponses;
	std::vector<ContactResponse> mResponsesWithSystem;

	void elementCollisionResponse(Entity * e);

};

