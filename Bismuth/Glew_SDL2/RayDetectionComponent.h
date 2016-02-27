#pragma once

#include "DetectionComponent.h"
#include "glm/gtx/rotate_vector.hpp"

class RayDetectionComponent : public DetectionComponent
{

public:
	RayDetectionComponent();
	~RayDetectionComponent();
	Shape getShape() const { return RAY; }
	float getRadius() const { return 0; }

private:


};
