#pragma once
#include "DetectionComponent.h"
#include "StateComponent.h"
#include "DetectionProcessor.h"

#include <set>
#include "glm.hpp"
#include "Observer_Input.h"

class DetectionComponent;
class StateComponent;




class PhysicComponent : public Observer_Input
{
public :
    PhysicComponent(DetectionComponent* detectionComponent, StateComponent* stateComponent);
    ~PhysicComponent();


	DetectionComponent* getDetectionComponent(){ return mDetectionComponent; }
	StateComponent* getStateComponent(){ return mStateComponent; }




	void move(glm::vec2 mouse, glm::vec2 mouseRelative);
	void click(glm::vec2 mouse);
	void unclick(glm::vec2 mouse);
	void tick();


private :

    DetectionComponent* mDetectionComponent;
    StateComponent* mStateComponent;


};
