#include "PhysicComponent.h"

using namespace glm;

PhysicComponent::PhysicComponent(DetectionComponent* detectionComponent, StateComponent* stateComponent) :
    mDetectionComponent(detectionComponent), mStateComponent(stateComponent)
{}

PhysicComponent::~PhysicComponent()
{
    delete mDetectionComponent;
    delete mStateComponent;
}

void PhysicComponent::getCollision(PhysicComponent* phyComp2)
{
	if (mStateComponent->hasCollision() && phyComp2->getStateComponent()->hasCollision())
	{

		Contact* contact = mDetectionComponent->getCollision(mStateComponent->getPosition(), mStateComponent->getRotation(),
			phyComp2->getStateComponent()->getPosition(), phyComp2->getStateComponent()->getRotation(), phyComp2->getDetectionComponent());

		if (contact != nullptr)
		{
			contact->who = phyComp2;
			mContact.insert(contact);
			
			Contact* contact2 = new Contact;
			contact2->position = contact->position;
			contact2->normal = - contact->normal;
			contact2->who = this;

			phyComp2->mContact.insert(contact2);

		}
		
	} 
}

void PhysicComponent::clearContact()
{
	for (std::set<Contact*>::iterator it = mContact.begin(); it != mContact.end(); it++)
	{
		delete *it;
	}
	mContact.clear();
}

void PhysicComponent::responseToContact(Contact *contact)
{

	StateComponent *sc1 = mStateComponent, *sc2 = contact->who->getStateComponent();
	vec3 vr = sc2->getPositionDiff() - sc1->getPositionDiff();

	float numJr = -dot(vr, contact->normal);

	float denJr_1 = cross(inverse(sc1->getInertia()) * cross(sc1->getPosition(), contact->normal), sc1->getPosition()),
		denJr_2 = cross(inverse(sc2->getInertia()) * cross(sc2->getPosition(), contact->normal), sc2->getPosition()),
		denJr_3 = dot(denJ_1 + denJ_2, contact->normal),
		denJr = 1 / sc1->getMass() + 1 / sc2->getMass() + denJ_3;

	float jr = numJr / denJr;


	sc1->setPositionDiff(sc1->getPositionDiff() - (jr / sc1->getMass())*contact->normal);
}

void PhysicComponent::collisionResponse(float timestep)
{
	if (mContact.size() == 0)
		return;
	else if (mContact.size() == 1)
	{

	}
	else
	{

	}
}