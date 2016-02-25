#include "UserCamera.h"


using namespace glm;

UserCamera::UserCamera(Camera* camera) : mRotationDiff(0), mPositionDiff(0),mCamera(camera), mode(0)
{
	
}


UserCamera::~UserCamera()
{
}

void UserCamera::update(Input &input, double elapsedTime)
{
	if (input.getRisingKey(SDL_SCANCODE_F))
	{
		mode = (mode + 1) % 2;
		mCamera->capturePointer(!mode);
	}

	if (mode == 0) update1(input, elapsedTime);
	if (mode == 1) update2(input, elapsedTime);
}

void UserCamera::update1(Input &input, double elapsedTime)
{
	vec3 side = normalize(cross(mCamera->getRotation(), mCamera->getUp()));
	vec3 up = normalize(cross(mCamera->getRotation(), side));

	float  forward = max( (float)(input.getKey(SDL_SCANCODE_W))  , (float)(input.getKey(SDL_SCANCODE_Z)));
	float backward = max((float)(input.getKey(SDL_SCANCODE_S)), (float)(input.getKey(SDL_SCANCODE_S)));
	float left	   = max((float)(input.getKey(SDL_SCANCODE_A)), (float)(input.getKey(SDL_SCANCODE_Q)));
	float right    = max((float)(input.getKey(SDL_SCANCODE_D)), (float)(input.getKey(SDL_SCANCODE_D)));


	mPositionDiff += (forward - backward) * normalize(mCamera->getRotation()) / 1000.0f
		- (left - right) * side / 1000.0f
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

void UserCamera::update2(Input &input, double elapsedTime)
{
	vec3 side = normalize(cross(mCamera->getRotation(), mCamera->getUp()));
	vec3 up = normalize(cross(mCamera->getRotation(), side));

	if (input.getMouseButton(1))
	{
		mRotationDiff += (float)input.getRX()  * side / 10000.0f
			+ (float)input.getRY()  * up / 10000.0f;
	}

	mPositionDiff += (float)(input.getKey(SDL_SCANCODE_W) - input.getKey(SDL_SCANCODE_S)) * normalize(mCamera->getRotation()) / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_A) - input.getKey(SDL_SCANCODE_D)) * side / 1000.0f
		- (float)(input.getKey(SDL_SCANCODE_SPACE) - input.getKey(SDL_SCANCODE_LCTRL))* up / 1000.0f;

	//FRICTION
	mPositionDiff *= 0.94f;
	mRotationDiff *= 0.10f;
	//TRAJECTOIRE


	mCamera->setPosition(mCamera->getPosition() + mPositionDiff*float(elapsedTime));
	mCamera->setRotation(mCamera->getRotation() + 30 * length(mCamera->getRotation())*mRotationDiff*float(elapsedTime));

}