#include "DetectionComponent.h"



Contact* DetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2)
{

	Contact* result;
	switch (detComp2->getShape())
	{
	case RAY:
		result = getCollisionOnRay(pos1, rot1, pos2, rot2, detComp2);
		break;

	case SPHERE:
		result = getCollisionOnSphere(pos1, rot1, pos2, rot2, detComp2);
		break;

	case CUBE:
		result = getCollisionOnCube(pos1, rot1, pos2, rot2, detComp2);
		break;


	default: result = nullptr;
		break;
	}

	return result;


}