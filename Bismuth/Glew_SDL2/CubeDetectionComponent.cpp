#include "CubeDetectionComponent.h"



CubeDetectionComponent::CubeDetectionComponent(float sizeX, float sizeY, float sizeZ):
	mSizeX(sizeX), mSizeY(sizeY), mSizeZ(sizeZ)
{

}
CubeDetectionComponent::~CubeDetectionComponent()
{

}


Contact* CubeDetectionComponent::getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}
Contact* CubeDetectionComponent::getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}
Contact* CubeDetectionComponent::getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}