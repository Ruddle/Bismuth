#pragma once

#include "DetectionComponent.h"
#include "glm\gtx\rotate_vector.hpp"

class PlaneDetectionComponent : public DetectionComponent
{

public:

	PlaneDetectionComponent(float sizeX, float sizeY);
	~PlaneDetectionComponent();

	Shape getShape() const { return PLANE; }
	float getSizeX() const { return mSizeX; }
	float getSizeY() const { return mSizeY; }


private:

	float mSizeX;
	float mSizeY;
};