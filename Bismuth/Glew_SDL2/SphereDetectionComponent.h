#pragma once

#include "DetectionComponent.h"
#include "glm\gtx\rotate_vector.hpp"


class SphereDetectionComponent : public DetectionComponent
{

public:
	SphereDetectionComponent(float radius2);
	~SphereDetectionComponent();
	

	Shape getShape() const {return SPHERE;}
	float getRadius2() const { return mRadius2; }
	float getRadius() const { return mRadius; }

private:

	float mRadius2;
	float mRadius;



};