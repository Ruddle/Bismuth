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



void PhysicComponent::move(glm::vec2 mouse, glm::vec2 mouseRelative)
{
}

void PhysicComponent::click(glm::vec2 mouse)
{



}

void PhysicComponent::unclick(glm::vec2 mouse)
{
}

void PhysicComponent::tick()
{
}

