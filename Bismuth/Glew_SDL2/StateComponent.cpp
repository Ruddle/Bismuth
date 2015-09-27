#include "StateComponent.h"

using namespace glm;


StateComponent::StateComponent() : mHasCollision(true), mHasForce(true), mHasGravity(true), mHasTorque(true), mHasUpdate(true), mIsSleeping(false),
									mPosition(0), mPositionDiff(0), mRotation(0), mRotationDiff(0),
									mMass(1),mInertia(1)
{

}

StateComponent::~StateComponent()
{

}


void StateComponent::force(glm::vec3 force)
{
	mPosition += force / mMass;
}
void StateComponent::force(glm::vec3 force, glm::vec3 pt)
{
	this->force(force);
	vec3 OM = pt - mPosition;
	this->torque(cross(OM, force));
}
void StateComponent::torque(glm::vec3 torque)
{
	mRotationDiff += mInertia*torque;
}

void StateComponent::friction(float coeff)
{
	mPositionDiff /= (1 + coeff);
	mRotationDiff /= (1 + coeff);
}

void StateComponent::update(int time)
{
	mPosition += mPositionDiff*float(time);
	mRotation += mRotationDiff*float(time);

	mRotation = mod(mRotation + vec3((float)M_PI), vec3(2 * (float)M_PI));

	if (mRotation.x < 0)
		mRotation.x += 2 * (float)M_PI;
	if (mRotation.y < 0)
		mRotation.y += 2 * (float)M_PI;
	if (mRotation.z < 0)
		mRotation.z += 2 * (float)M_PI;

	mRotation.x -= (float)M_PI;

	mRotation.y -= (float)M_PI;

	mRotation.z -= (float)M_PI;
}