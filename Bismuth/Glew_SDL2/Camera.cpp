#include "Camera.h"

using namespace glm;

Camera::Camera(double fovInDegree, double aspect, double near, double far) :
	mNear(near), mFar(far), mAspect(aspect), mode(0), mPosition(vec3(0,-4,2)), mPositionDiff(0), mRotation(vec3(0,1,0)), mRotationDiff(0), mUp(vec3(0, 0, 1))
{
	mProjection =   glm::perspective(fovInDegree*M_PI / 180.0, aspect, near,far);
	mTanHalfFov = tan((fovInDegree*M_PI / 180.0) / 2.0);
}

Camera::~Camera()
{


}

void Camera::update(Input &input, double elapsedTime)
{
	vec3 side = normalize(cross(mRotation, mUp));
	vec3 up = normalize(cross(mRotation, side));

	mPositionDiff += (float)(input.getKey(SDL_SCANCODE_W) - input.getKey(SDL_SCANCODE_S)) * normalize(mRotation) / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_A) - input.getKey(SDL_SCANCODE_D)) * side / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_SPACE) - input.getKey(SDL_SCANCODE_LCTRL))* up / 1000.0f;


	mRotationDiff += (float)input.getRX()  * side    / 10000.0f
					+(float)input.getRY()  * up		 / 10000.0f;


	//FRICTION
	mPositionDiff *= 0.94f;
	mRotationDiff *= 0.10f;
	//TRAJECTOIRE
	mPosition += mPositionDiff*float(elapsedTime);
	mRotation += 30*length(mRotation)*mRotationDiff*float(elapsedTime);

	if(length(mRotation)>1)
	mRotation = (mRotation)*0.5f;

}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(
		mPosition,
		mPosition + mRotation,
		mUp); 
}

