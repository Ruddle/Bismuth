#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"


class SphereDetectionComponent : public DetectionComponent
{

public:
	SphereDetectionComponent(float radius2);
	~SphereDetectionComponent();
	

	int getShape() const {return SPHERE;}
	float getRadius2() const { return mRadius2; }

private:

	float mRadius2;



};