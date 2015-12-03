#include "StateComponent.h"
#include "glm.hpp"
#include "glm\gtx\rotate_vector.hpp"

using namespace glm;


StateComponent::StateComponent() : mHasDetection(true),mHasResponse(true), mHasForce(true), mHasGravity(true), mHasTorque(true),
									mHasUpdate(true), mIsSleeping(false),
									mPosition(0), mPositionDiff(0), mRotation(1,0.0, 0.0, 0.0), mRotationDiff(0),
									mMass(1),mInertia(1.0/6.0), mModel(0), mModelInv(0), mLastModel(0),mRestitution(0.7)
									, mInertiaInverse(1)
{
	mInertiaInverse = inverse(mat3(1));
}

StateComponent::~StateComponent()
{

}


void StateComponent::force(float time_s, glm::vec3 const& force)
{
	mPositionDiff += time_s*force / mMass;
}
void StateComponent::force(float time_s, glm::vec3 const&  force, glm::vec3 const&  pt)
{
	this->force(time_s,force);
	vec3 OM = pt - mPosition;
	this->torque(time_s,cross(OM, force));
}
void StateComponent::torque(float time_s, glm::vec3 const&  torque)
{
	mRotationDiff += time_s*mInertiaInverse*torque;
}

void StateComponent::friction(float coeff)
{
	mPositionDiff /= (1 + coeff);
	mRotationDiff /= (1 + coeff);
}

void StateComponent::update(float time_s)
{
	mPosition += mPositionDiff*float(time_s);

	if (mRotationDiff != vec3(0))
	{
		quat q = quat(0, mRotationDiff*float(time_s));
		mRotation = mRotation + 0.5f * q * mRotation;
	}
	
	mRotation = normalize(mRotation);
	mLastModel = mModel;
	mModel = translate(mPosition)* mat4_cast(mRotation);
	mModelInv = inverse(mModel);
}

