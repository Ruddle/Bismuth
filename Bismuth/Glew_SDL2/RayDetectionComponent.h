#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"

class RayDetectionComponent : public DetectionComponent
{

public:
	RayDetectionComponent();
	~RayDetectionComponent();
	int getShape() const { return RAY; }

private:


};