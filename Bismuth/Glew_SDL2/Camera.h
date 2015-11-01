#pragma once

#include "glm.hpp"
#include "PhysicComponent.h"

class Camera
{
public:
	Camera(double fov, double aspect, double near,double far, glm::mat4 &view);
	~Camera();
	glm::mat4 getProjection() const { return mProjection; }
	glm::mat4 getView() const { return mView; }

	double getTanHalfFov()const { return mTanHalfFov; }
	double getAspect()const { return mAspect; }
	double getNear()const { return mNear; }
	double getFar()const { return mFar; }

private:

	glm::mat4 mProjection;
	glm::mat4 mView;
	double mTanHalfFov;
	double mAspect;
	double mNear;
	double mFar;
};
