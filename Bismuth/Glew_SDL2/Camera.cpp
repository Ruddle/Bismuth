#include "Camera.h"

Camera::Camera(double fovInDegree, double aspect, double near, double far, glm::mat4 &view) : mView(view), mNear(near), mFar(far),mAspect(aspect)
{
	mProjection =   glm::perspective(fovInDegree*M_PI / 180.0, aspect, near,far);
	mTanHalfFov = tan((fovInDegree*M_PI / 180.0) / 2.0);
}

Camera::~Camera()
{


}