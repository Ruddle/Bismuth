#include "UserCamera.h"


using namespace glm;

UserCamera::UserCamera(Camera* camera) : mRotationDiff(0), mPositionDiff(0),mCamera(camera)
{
}


UserCamera::~UserCamera()
{
}

void UserCamera::update(Input &input, double elapsedTime)
{
	vec3 side = normalize(cross(mCamera->getRotation(), mCamera->getUp()));
	vec3 up = normalize(cross(mCamera->getRotation(), side));

	mPositionDiff += (float)(input.getKey(SDL_SCANCODE_W) - input.getKey(SDL_SCANCODE_S)) * normalize(mCamera->getRotation()) / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_A) - input.getKey(SDL_SCANCODE_D)) * side / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_SPACE) - input.getKey(SDL_SCANCODE_LCTRL))* up / 1000.0f;


	mRotationDiff += (float)input.getRX()  * side / 10000.0f
		+ (float)input.getRY()  * up / 10000.0f;


	//FRICTION
	mPositionDiff *= 0.94f;
	mRotationDiff *= 0.10f;
	//TRAJECTOIRE

	mCamera->setPosition(mCamera->getPosition() + mPositionDiff*float(elapsedTime));
	mCamera->setRotation(mCamera->getRotation() + 30 * length(mCamera->getRotation())*mRotationDiff*float(elapsedTime));
	


}