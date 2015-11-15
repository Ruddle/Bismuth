#include "CubeDetectionComponent.h"

using namespace glm;

CubeDetectionComponent::CubeDetectionComponent(float sizeX, float sizeY, float sizeZ):
	mSizeX(sizeX), mSizeY(sizeY), mSizeZ(sizeZ)
{
	mRadius = sqrt(sizeX*sizeX + sizeY*sizeY + sizeZ*sizeZ) / 2.0f;
}
CubeDetectionComponent::~CubeDetectionComponent()
{

}
