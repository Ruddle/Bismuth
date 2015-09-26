#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\glm.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class StateComponent
{
public:
	StateComponent();
	~StateComponent();

	void force(glm::vec3 force);
	void force(glm::vec3 force, glm::vec3 point);
	void torque(glm::vec3 torque); // en O
	void friction(float coeff);
	void update(int time);

	glm::vec3 getPosition() { return mPosition; }
	glm::vec3 getPositionDiff() { return mPositionDiff; }
	glm::vec3 getRotation() { return mRotation; }
	glm::vec3 getRotationDiff() { return mRotationDiff; }

	bool hasCollision() { return mHasCollision; }
	bool hasGravity() { return mHasGravity; }
	bool hasUpdate() { return mHasUpdate; }
	bool hasTorque() { return mHasTorque; }
	bool hasForc() { return mHasForce; }
	bool isSleeping() { return mIsSleeping; }

	void setPosition(glm::vec3 value) { mPosition = value; }
	void setPositionDiff(glm::vec3 value) { mPositionDiff = value; }
	void setRotation(glm::vec3 value) { mRotation = value; }
	void setRotationDiff(glm::vec3 value) { mRotationDiff = value; }

private:

	float mMass;
	glm::mat3 mInertia;

	glm::vec3 mPosition;
	glm::vec3 mPositionDiff;

	glm::vec3 mRotation;
	glm::vec3 mRotationDiff;

	bool mHasCollision;
	bool mHasGravity;
	bool mHasUpdate;
	bool mHasTorque;
	bool mHasForce;
	bool mIsSleeping;

};
