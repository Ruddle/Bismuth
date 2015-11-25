#pragma once
#include "DetectionComponent.h"
#include "StateComponent.h"
#include "DetectionProcessor.h"

#include <set>
#include "glm.hpp"

class DetectionComponent;
class StateComponent;


class PhysicComponent
{
public :
    PhysicComponent(DetectionComponent* detectionComponent, StateComponent* stateComponent);
    ~PhysicComponent();
    void getCollision(PhysicComponent* phyComp2);
	void collisionResponse(float timestep);
	void responseToContact(float elapsedTime,Contact *contact);

	DetectionComponent* getDetectionComponent(){ return mDetectionComponent; }
	StateComponent* getStateComponent(){ return mStateComponent; }
	std::set<Contact*>  getContact() { return mContact; }
	void clearContact();

private :

    DetectionComponent* mDetectionComponent;
    StateComponent* mStateComponent;
	std::set<Contact*> mContact;

};
