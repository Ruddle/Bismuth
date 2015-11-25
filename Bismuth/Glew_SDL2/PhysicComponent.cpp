#include "PhysicComponent.h"

#include <iostream>

using namespace glm;
using namespace std;

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
	if (mStateComponent->hasDetection() && phyComp2->getStateComponent()->hasDetection())
	{

		Contact* contact = DetectionProcessor::detection(mDetectionComponent, phyComp2->getDetectionComponent(),
														mStateComponent->getPosition(), mStateComponent->getRotation(),
														phyComp2->getStateComponent()->getPosition(), phyComp2->getStateComponent()->getRotation());

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

void PhysicComponent::responseToContact(float elapsedTime,Contact *contact)
{

	StateComponent *sc1 = mStateComponent, *sc2 = contact->who->getStateComponent();
	vec3 r1 = contact->position - sc1->getPosition(), r2 = contact->position - sc2->getPosition();
	vec3 vp1 = sc1->getPositionDiff() + cross(sc1->getRotationDiff(), r1);
	vec3 vp2 = sc2->getPositionDiff() + cross(sc2->getRotationDiff(), r2);
	vec3 vr = vp2 - vp1;
	cout << length(vr)*1000.0 << endl;
	mat3 invI1 = sc1->getInertiaInverse(), invI2 = sc2->getInertiaInverse();
	float e = (sc2->getRestitution() + sc1->getRestitution()) / 2;
	vec3 normalized = normalize(contact->normal);
	float numJr = -(1+e)*dot(vr, normalized);
	vec3 denJr_1 = invI1 *cross(cross(r1, normalized), r1);
	vec3 denJr_2 = invI2 *cross(cross(r2, normalized), r2);
	float denJr_3 = dot(denJr_1 + denJr_2, normalized),
		denJr = (1/sc1->getMass()) + (1/sc2->getMass()) + denJr_3;
	float jr = numJr / denJr;
	sc1->setPositionDiff(sc1->getPositionDiff() - (jr / sc1->getMass())*normalized);
	sc1->setRotationDiff(sc1->getRotationDiff() - jr*invI1*cross(r1, normalized) *vec3(1)  );
	sc1->setPosition(sc1->getPosition() - (sc2->getMass() / (sc1->getMass() + sc2->getMass()))*contact->normal*1.01f);


	//StateComponent *sc1 = mStateComponent, *sc2 = contact->who->getStateComponent();
	//sc1->force(elapsedTime ,-contact->normal*0.08f, contact->position);






}

void PhysicComponent::collisionResponse(float timestep)
{
	if (mContact.size() == 0 || !mStateComponent->hasResponse())
		return;
	else if (mContact.size() == 1)
	{
		responseToContact(timestep,*mContact.begin());
	}
	else
	{
		responseToContact(timestep,*mContact.begin());
	}
}