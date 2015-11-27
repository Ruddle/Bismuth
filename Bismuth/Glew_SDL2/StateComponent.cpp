#include "StateComponent.h"
#include "glm.hpp"
#include "glm\gtx\rotate_vector.hpp"

using namespace glm;


StateComponent::StateComponent() : mHasDetection(true),mHasResponse(true), mHasForce(true), mHasGravity(true), mHasTorque(true),
									mHasUpdate(true), mIsSleeping(false),
									mPosition(0), mPositionDiff(0), mRotation(1,0.0, 0.0, 0.0), mRotationDiff(0),
									mMass(1),mInertia(1.0/6.0), mModel(0), mModelInv(0), mLastModel(0),mRestitution(0.3)
									, mInertiaInverse(1)
{
	mInertiaInverse = inverse(mat3(1));
}

StateComponent::~StateComponent()
{

}


void StateComponent::force(float time, glm::vec3 const& force)
{
	mPositionDiff += time*force / mMass;
}
void StateComponent::force(float time, glm::vec3 const&  force, glm::vec3 const&  pt)
{
	this->force(time,force);
	vec3 OM = pt - mPosition;
	this->torque(time,cross(OM, force));
}
void StateComponent::torque(float time, glm::vec3 const&  torque)
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



	if (mRotationDiff != vec3(0))
	{


		quat q = quat(0, mRotationDiff*float(time));

		mRotation = mRotation + 0.5f * q * mRotation;
	}
	

	mRotation = normalize(mRotation);

	mLastModel = mModel;
	
	mModel = translate(mPosition)* mat4_cast(mRotation);
	mModelInv = inverse(mModel);

}

