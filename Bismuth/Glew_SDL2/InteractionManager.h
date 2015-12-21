#pragma once
#include <vector>
#include "Entity.h"


struct Contact
{
	glm::vec3 position;
	glm::vec3 normal;
	PhysicComponent* who1;
	PhysicComponent* who2;
};

struct ContactResponse
{
	glm::vec3 normal;
	Screw screw1;
	Screw screw2;
	PhysicComponent* who1;
	PhysicComponent* who2;
};





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

