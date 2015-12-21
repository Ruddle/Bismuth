#include "InteractionManager.h"
#include "DetectionProcessor.h"


using namespace glm;

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

	mResponses.clear();

	for (int i = 0; i < mContacts.size(); i++)
	{	
		StateComponent *sc1 = mContacts[i]->who1->getStateComponent(), *sc2 = mContacts[i]->who2->getStateComponent();
		vec3 r1 = mContacts[i]->position  - sc1->getPosition(), r2 = mContacts[i]->position - sc2->getPosition();
		vec3 vp1 = sc1->getPositionDiff() + cross(sc1->getRotationDiff(), r1);
		vec3 vp2 = sc2->getPositionDiff() + cross(sc2->getRotationDiff(), r2);
		vec3 vr = vp2 - vp1;
		
		mat3 invI1 = sc1->getInertiaInverse(), invI2 = sc2->getInertiaInverse();
		float e = (sc2->getRestitution() + sc1->getRestitution()) / 2;

		vec3 normalized = normalize(mContacts[i]->normal);
		float numJr = -(1 + e)*dot(vr, normalized);
		vec3 denJr_1 = invI1 *cross(cross(r1, normalized), r1);
		vec3 denJr_2 = invI2 *cross(cross(r2, normalized), r2);
		float denJr_3 = dot(denJr_1 + denJr_2, normalized),
			denJr = (1 / sc1->getMass()) + (1 / sc2->getMass()) + denJr_3;
		float jr = numJr / denJr;

		ContactResponse response;
		response.r1 = r1;
		response.r2 = r2;
		response.normal = mContacts[i]->normal;
		response.who1 = mContacts[i]->who1;
		response.who2 = mContacts[i]->who2;
		mResponses.push_back(response);


		//response.posDiff2 = -(jr / sc1->getMass())*normalized;
		//mat4 toRotCube = inverse(mat4(mat3(sc1->getModel())));
		//vec3 axis = vec3(toRotCube*vec4(cross(r1, normalized), 1));
		//axis = cross(r1, normalized);
		//response.rotDiff = -jr*invI1*axis;
		//response.posDiff = -(sc2->getMass() / (sc1->getMass() + sc2->getMass()))*contact->normal*1.01f;
		//return response;
	}
}

void InteractionManager::systemCollisionResponse()
{
}
