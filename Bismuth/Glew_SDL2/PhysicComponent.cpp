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

	mat3x3 invI1 = inverse(sc1->getInertia()), invI2 = inverse(sc2->getInertia());

	float numJr = -dot(vr, contact->normal);

	vec3 denJr_1 = cross(invI1 * cross(sc1->getPosition(), contact->normal), sc1->getPosition()),
		denJr_2 = cross(invI2 * cross(sc2->getPosition(), contact->normal), sc2->getPosition());
	float denJr_3 = dot(denJr_1 + denJr_2, contact->normal),
		denJr = 1 / sc1->getMass() + 1 / sc2->getMass() + denJr_3;

	float jr = numJr / denJr;


	sc1->setPositionDiff(sc1->getPositionDiff() - (jr / sc1->getMass())*contact->normal);
	sc1->setRotationDiff(sc1->getRotationDiff() - jr*invI1*cross(sc1->getPosition(), contact->normal));
}

void PhysicComponent::collisionResponse(float timestep)
{
	if (mContact.size() == 0 || !mStateComponent->hasResponse())
		return;
	else if (mContact.size() == 1)
	{
		responseToContact(*mContact.begin());
	}
	else
	{
		// Fuck it
	}
}