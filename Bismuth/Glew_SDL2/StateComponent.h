#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm.hpp"
#include "glm\gtx\rotate_vector.hpp"
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
	void update(float time);

	glm::mat4 getModel() { return mModel; }
	glm::mat4 getLastModel() { return mLastModel; }
	glm::vec3 getPosition() { return mPosition; }
	glm::vec3 getPositionDiff() { return mPositionDiff; }
	glm::vec3 getRotation() { return mRotation; }
	glm::vec3 getRotationDiff() { return mRotationDiff; }

	float getMass() { return mMass; }
	glm::mat3 getInertia() { return mInertia; }

	void setMass(float mass) { mMass = mass; }
	void setInertia(glm::mat3 inertia) { mInertia = inertia; }
	void setInertia(float inertia) { setInertia(glm::mat3(inertia)); }

	glm::vec3 getPositionPast(float ms) { return mPosition - mPositionDiff*ms; }
	glm::vec3 getRotationPast(float ms) { return mRotation - mRotationDiff*ms; }

	bool hasDetection() { return mHasDetection; }
	bool hasResponse() { return mHasResponse; }
	bool hasGravity() { return mHasGravity; }
	bool hasUpdate() { return mHasUpdate; }
	bool hasTorque() { return mHasTorque; }
	bool hasForce() { return mHasForce; }
	bool isSleeping() { return mIsSleeping; }

	void setPosition(glm::vec3 value) { mPosition = value; }
	void setPositionDiff(glm::vec3 value) { mPositionDiff = value; }
	void setRotation(glm::vec3 value) { mRotation = value;}
	void setRotationDiff(glm::vec3 value) { mRotationDiff = value; }

private:

	float mMass;
	glm::mat3 mInertia;

	glm::mat4 mModel;
	glm::mat4 mLastModel;
	glm::vec3 mPosition;
	glm::vec3 mPositionDiff;

	glm::vec3 mRotation;
	glm::vec3 mRotationDiff;

	bool mHasDetection;
	bool mHasResponse;
	bool mHasGravity;
	bool mHasUpdate;
	bool mHasTorque;
	bool mHasForce;
	bool mIsSleeping;

};
