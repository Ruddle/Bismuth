#include "InteractionManager.h"
#include "DetectionProcessor.h"
#include "Mesh.h"

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
		if (entity_i != nullptr && entity_i->getType() == Entity::MESH)
		{
			for (int j = i + 1; j < mEntities.size(); j++)
			{
				Entity *entity_j = mEntities[j];
				if (entity_j != nullptr && entity_j->getType() == Entity::MESH)
				{
					PhysicComponent *phyI = ((Mesh*)entity_i)->getPhysicComponent(), *phyJ = ((Mesh*)entity_j)->getPhysicComponent();
					Contact* contact = DetectionProcessor::detection(phyI, phyJ);


					if (contact != nullptr)
					{
						mContacts.push_back(contact);
					}

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

	//	mat4 toRotCube1 = inverse(mat4(mat3(sc1->getModel())));
	//	vec3 axis1 = vec3(toRotCube1*vec4(cross(r1, normalized), 1));
		vec3 axis1 = cross(r1, normalized);

	//	mat4 toRotCube2 = inverse(mat4(mat3(sc2->getModel())));
	//	vec3 axis2 = vec3(toRotCube2*vec4(cross(r2, normalized), 1));
		vec3 axis2 = cross(r2, normalized);

		Screw screw1 = { -jr*invI1*axis1,  -(jr / sc1->getMass())*normalized   , r1};
		Screw screw2 = { +jr*invI2*axis2 , +(jr / sc2->getMass())*normalized ,   r2};

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

	for (int i = 0; i < mResponses.size(); i++)
	{
		ContactResponse cr = mResponses[i];

		PhysicComponent*  w1 = cr.who1;
		PhysicComponent*  w2 = cr.who2;
		glm::vec3 n = cr.normal;
		Screw s1 = cr.screw1;
		Screw s2 = cr.screw2;

		float m1 = w1->getStateComponent()->getMass(), m2 = w2->getStateComponent()->getMass();
		float totalMass = m1 + m2;

		w1->getStateComponent()->setPosition(w1->getStateComponent()->getPosition() - n*m2/totalMass);
		w2->getStateComponent()->setPosition(w2->getStateComponent()->getPosition() + n*m1 / totalMass);


		w1->getStateComponent()->torque(1.0, s1.s);
		w1->getStateComponent()-> force(1.0, s1.v);

		w2->getStateComponent()->torque(1.0, s2.s);
		w2->getStateComponent()-> force(1.0, s2.v);
	}


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
