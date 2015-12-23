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

		mat4 toRotCube1 = inverse(mat4(mat3(sc1->getModel())));
		vec3 axis1 = vec3(toRotCube1*vec4(cross(r1, normalized), 1));
		axis1 = cross(r1, normalized);

		Screw screw1 = { -(jr / sc1->getMass())*normalized  ,  -jr*invI1*axis1 , r1};
		Screw screw2 = { +(jr / sc2->getMass())*normalized  ,  +jr*invI2*axis1 , r2};


		ContactResponse response;
		response.screw1 = screw1;
		response.screw2 = screw2;
		response.normal = mContacts[i]->normal;
		response.who1 = mContacts[i]->who1;
		response.who2 = mContacts[i]->who2;
		mResponses.push_back(response);


	
	}
}

void InteractionManager::systemCollisionResponse()
{
	//for (int i = 0; i < mResponses.size(); i++)
	//{
	//	PhysicSystem* phySysA = mResponses[i].who1->getSystem();
	//	PhysicSystem* phySysB = mResponses[i].who2->getSystem();

	//	if (phySysA == nullptr)
	//	{
	//		//Calcul facile de la force
	//	}
	//	else
	//	{
	//		//Prise en compte du system
	//		elementCollisionResponse(mResponses[i].who1);
	//	}


	//	if (phySysB == nullptr)
	//	{
	//		//Calcul facile de la force
	//	}
	//	else
	//	{
	//		elementCollisionResponse(mResponses[i].who2);
	//	}
	//}
}

void InteractionManager::doResponse()
{


}

void InteractionManager::elementCollisionResponse(Entity * e)
{
	/*PhysicSystem* phySys = e->getSystem();

	bool end = 0;

	while (end == 0)
	{
		vector<Constraint*> constraints = phySys->getConstraints(e);

		

	}*/
}
