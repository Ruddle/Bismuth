#include "PlaneDetectionComponent.h"



PlaneDetectionComponent::PlaneDetectionComponent(float sizeX, float sizeY) :
	mSizeX(sizeX), mSizeY(sizeY)
{
	mRadius = sqrt(sizeX*sizeX + sizeY*sizeY) / 2.0f;
}
PlaneDetectionComponent::~PlaneDetectionComponent()
{

}

