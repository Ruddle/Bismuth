#include "Camera.h"

using namespace glm;

Camera::Camera(double fovInDegree, double aspect, double near, double far) :
	mNear(near), mFar(far), mAspect(aspect), mode(0), mPosition(vec3(0,-4,2)),  mRotation(vec3(0,1,0)),  mUp(vec3(0, 0, 1))
{
	mProjection =   glm::perspective(fovInDegree*M_PI / 180.0, aspect, near,far);
	mTanHalfFov = tan((fovInDegree*M_PI / 180.0) / 2.0);
}

Camera::~Camera()
{


}

void Camera::capturePointer(bool b)
{
	 mPointer=b;

	 SDL_SetRelativeMouseMode(SDL_FALSE);
	 if(b)
	 SDL_SetRelativeMouseMode(SDL_TRUE); 
}



glm::mat4 Camera::getView() const
{
	return glm::lookAt(
		mPosition,
		mPosition + mRotation,
		mUp); 
}

