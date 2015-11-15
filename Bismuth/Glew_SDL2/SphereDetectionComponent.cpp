#include "SphereDetectionComponent.h"

using namespace glm;

SphereDetectionComponent::SphereDetectionComponent(float radius) :mRadius2(radius*radius)
{
	mRadius = radius;
}

SphereDetectionComponent::~SphereDetectionComponent()
{

}

