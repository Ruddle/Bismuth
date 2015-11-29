#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"
#include "Input.h"


class Camera
{
public:
	Camera(double fov, double aspect, double near,double far);
	~Camera();
	
	void capturePointer(bool b);

	glm::mat4 getProjection() const { return mProjection; }
	glm::mat4 getView() const;
	double getTanHalfFov()const { return mTanHalfFov; }
	double getAspect()const { return mAspect; }
	double getNear()const { return mNear; }
	double getFar()const { return mFar; }
	glm::vec3 getPosition() { return mPosition; }
	glm::vec3 getRotation() { return mRotation; }
	glm::vec3 getUp() { return mUp; }


	void setPosition(glm::vec3 value) { mPosition = value; }
	void setRotation(glm::vec3 value) { mRotation = value;	if (length(mRotation)>1)mRotation = (mRotation)*0.5f;}
	





private:

	glm::mat4 mProjection;
	
	bool mPointer;

	double mTanHalfFov;
	double mAspect;
	double mNear;
	double mFar;

	glm::vec3 mPosition;


	glm::vec3 mRotation;


	glm::vec3 mUp;

	int mode;



};
