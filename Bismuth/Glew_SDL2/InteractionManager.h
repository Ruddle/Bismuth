#pragma once
#include <vector>
#include "Entity.h"
#include "PhysicComponent.h"
#include "Screw.h"
#include "Forcefield.h"




class InteractionManager
{
public:
	InteractionManager(std::vector<Entity*> &entities);
	~InteractionManager();
	void collision();
	void singleCollisionResponse(float elapsedTime);
	void systemCollisionResponse();
	void doResponse();

	std::vector<ContactEntity*> getContacts() { return mContactsEntity; }

private:
	std::vector<Entity*> &mEntities;
	std::vector<ContactEntity*> mContactsEntity;
	std::vector<ContactResponse> mResponses;
	std::vector<ContactResponse> mResponsesWithSystem;

	void elementCollisionResponse(Entity * e);

};

