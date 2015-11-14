#include "RayDetectionComponent.h"

RayDetectionComponent::RayDetectionComponent()
{

}
RayDetectionComponent::~RayDetectionComponent()
{

}


Contact* RayDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2)
{
	return nullptr;
}
Contact* RayDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollision(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}
Contact* RayDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollision(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}
Contact* RayDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent *detComp2)
{
	Contact* result = detComp2->getCollision(pos2, rot2, pos1, rot1, this);
	result->normal = -result->normal;
	return result;
}