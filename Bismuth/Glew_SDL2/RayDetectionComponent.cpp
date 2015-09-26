#include "RayDetectionComponent.h"

RayDetectionComponent::RayDetectionComponent()
{

}
RayDetectionComponent::~RayDetectionComponent()
{

}


Contact* RayDetectionComponent::getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	return nullptr;
}
Contact* RayDetectionComponent::getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollisionOnRay(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}
Contact* RayDetectionComponent::getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollisionOnRay(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}