#pragma once
#include "Camera.h"
#include "glm.hpp"


class UserCamera
{
public:
	UserCamera(Camera* camera);
	~UserCamera();
	void update(Input &input, double elapsedTime);
	void update1(Input &input, double elapsedTime);
	void update2(Input &input, double elapsedTime);

	void setRotationDiff(glm::vec3 value) { mRotationDiff = value; }
	void setPositionDiff(glm::vec3 value) { mPositionDiff = value; }
	
private:
	Camera* mCamera;
	glm::vec3 mPositionDiff;
	glm::vec3 mRotationDiff;
	int mode;
};

