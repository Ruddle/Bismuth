#pragma once

#include "DetectionComponent.h"
#include "glm\gtx\rotate_vector.hpp"
#include "glm.hpp"

class CubeDetectionComponent : public DetectionComponent
{

public:
	CubeDetectionComponent(float sizeX, float sizeY, float sizeZ);
	~CubeDetectionComponent();

	Shape getShape() const { return CUBE; }

	glm::vec3 getSize() const {return glm::vec3(mSizeX, mSizeY, mSizeZ); }


private:
	float mSizeX;
	float mSizeY;
	float mSizeZ;
};