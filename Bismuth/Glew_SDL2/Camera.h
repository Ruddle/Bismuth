#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"
#include "Input.h"

class Camera
{
public:
	Camera(double fov, double aspect, double near,double far);
	~Camera();
	
	void update(Input &input, double elapsedTime);
	
	glm::mat4 getProjection() const { return mProjection; }
	glm::mat4 getView() const;
	double getTanHalfFov()const { return mTanHalfFov; }
	double getAspect()const { return mAspect; }
	double getNear()const { return mNear; }
	double getFar()const { return mFar; }

	glm::vec3 getPosition() { return mPosition; }
	void setPosition(glm::vec3 value) { mPosition = value; }
	void setPositionDiff(glm::vec3 value) { mPositionDiff = value; }
	void setRotation(glm::vec3 value) { mRotation = value; }
	void setRotationDiff(glm::vec3 value) { mRotationDiff = value; }





private:

	glm::mat4 mProjection;
	

	double mTanHalfFov;
	double mAspect;
	double mNear;
	double mFar;

	glm::vec3 mPosition;
	glm::vec3 mPositionDiff;

	glm::vec3 mRotation;
	glm::vec3 mRotationDiff;

	glm::vec3 mUp;

	int mode;



};
