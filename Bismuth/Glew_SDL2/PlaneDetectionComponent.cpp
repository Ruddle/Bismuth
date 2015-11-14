#include "PlaneDetectionComponent.h"



PlaneDetectionComponent::PlaneDetectionComponent(float sizeX, float sizeY) :
	mSizeX(sizeX), mSizeY(sizeY)
{

}
PlaneDetectionComponent::~PlaneDetectionComponent()
{

}


Contact* PlaneDetectionComponent::getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}
Contact* PlaneDetectionComponent::getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}
Contact * PlaneDetectionComponent::getCollisionOnPlane(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent * detComp2)
{
	return nullptr;
}
Contact* PlaneDetectionComponent::getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollisionOnRay(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}
