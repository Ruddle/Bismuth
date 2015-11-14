#include "PlaneDetectionComponent.h"



PlaneDetectionComponent::PlaneDetectionComponent(float sizeX, float sizeY) :
	mSizeX(sizeX), mSizeY(sizeY)
{

}
PlaneDetectionComponent::~PlaneDetectionComponent()
{

}


Contact* PlaneDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2)
{
	return nullptr;
}
Contact* PlaneDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2)
{
	return nullptr;
}
Contact * PlaneDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent * detComp2)
{
	return nullptr;
}
Contact* PlaneDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollision(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}
