#pragma once
#include "DetectionComponent.h"
#include "StateComponent.h"
#include "Contact.h"
#include <set>

class DetectionComponent;
class StateComponent;
struct Contact;

class PhysicComponent
{
public :
    PhysicComponent(DetectionComponent* detectionComponent, StateComponent* stateComponent);
    ~PhysicComponent();
    void getCollision(PhysicComponent* phyComp2);

	DetectionComponent* getDetectionComponent(){ return mDetectionComponent; }
	StateComponent* getStateComponent(){ return mStateComponent; }
	std::set<Contact*>  getContact() { return mContact; }
	void clearContact();

private :

    DetectionComponent* mDetectionComponent;
    StateComponent* mStateComponent;
	std::set<Contact*> mContact;

};
