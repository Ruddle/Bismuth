#include "StateComponent.h"
#include "glm.hpp"
#include "glm\gtx\rotate_vector.hpp"

using namespace glm;


StateComponent::StateComponent() : mHasDetection(true),mHasResponse(true), mHasForce(true), mHasGravity(true), mHasTorque(true),
									mHasUpdate(true), mIsSleeping(false),
									mPosition(0), mPositionDiff(0), mRotation(0.0, 0.0, 1.0), mRotationDiff(0),
									mMass(1),mInertia(1.0/6.0), mModel(0), mModelInv(0), mLastModel(0),mRestitution(0.3)
									, mInertiaInverse(1)
{
	mInertiaInverse = inverse(mat3(1));
}

StateComponent::~StateComponent()
{

}


void StateComponent::force(float time, glm::vec3 force)
{
	mPositionDiff += time*force / mMass;
}
void StateComponent::force(float time, glm::vec3 force, glm::vec3 pt)
{
	this->force(time,force);
	vec3 OM = pt - mPosition;
	this->torque(time,cross(OM, force));
}
void StateComponent::torque(float time, glm::vec3 torque)
{
	mRotationDiff += time*mInertiaInverse*torque;
}

void StateComponent::friction(float coeff)
{
	mPositionDiff /= (1 + coeff);
	mRotationDiff /= (1 + coeff);
}

void StateComponent::update(float time)
{
	mPosition += mPositionDiff*float(time);
	mRotation += mRotationDiff*float(time);

	//mRotation = mod(mRotation + vec3((float)M_PI), vec3(2 * (float)M_PI));
	//if (mRotation.x < 0)
	//	mRotation.x += 2 * (float)M_PI;
	//if (mRotation.y < 0)
	//	mRotation.y += 2 * (float)M_PI;
	//if (mRotation.z < 0)
	//	mRotation.z += 2 * (float)M_PI;
	//mRotation.x -= (float)M_PI;
	//mRotation.y -= (float)M_PI;
	//mRotation.z -= (float)M_PI;

	mLastModel = mModel;
	//mModel = translate(mPosition)* rotate(mRotation.x, vec3(1, 0, 0)) *rotate(mRotation.y, vec3(0, 1, 0))*rotate(mRotation.z, vec3(0, 0, 1));
	//mModel = translate(mPosition)* eulerAngleYXZ(mRotation.y, mRotation.x, mRotation.z);
	mModel = translate(mPosition)* rotate(length(mRotation), normalize(mRotation));
	
	
	mModelInv = inverse(mModel);

}

