#include "CubeDetectionComponent.h"

using namespace glm;

CubeDetectionComponent::CubeDetectionComponent(float sizeX, float sizeY, float sizeZ):
	mSizeX(sizeX), mSizeY(sizeY), mSizeZ(sizeZ)
{

}
CubeDetectionComponent::~CubeDetectionComponent()
{

}


Contact* CubeDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2)
{
	return nullptr;
}
Contact* CubeDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2)
{
	Contact* result = nullptr;
	vec3 half = vec3(mSizeX / 2.0, mSizeY / 2.0, mSizeZ / 2.0);
	mat4 toWorldSpace = rotate(rot1.x, vec3(1, 0, 0)) *rotate(rot1.y, vec3(0, 1, 0))*rotate(rot1.z, vec3(0, 0, 1));
	mat4 toCubeSpace = inverse(toWorldSpace);

	vec3 relativePosSphere = vec3(toCubeSpace*vec4(pos2, 1));
	float radius = sqrt(((SphereDetectionComponent*)detComp2)->getRadius2());

	vec3 closestPoint = vec3(0);

	closestPoint = relativePosSphere;

	if (relativePosSphere.x > half.x)
		closestPoint.x = half.x;
	else if (relativePosSphere.x < -half.x)
		closestPoint.x = -half.x;

	if (relativePosSphere.y > half.y)
		closestPoint.y = half.y;
	else if (relativePosSphere.y < -half.y)
		closestPoint.y = -half.y;

	if (relativePosSphere.z > half.z)
		closestPoint.z = half.z;
	else if (relativePosSphere.z < -half.z)
		closestPoint.z = -half.z;


	vec3 relativePosSphereTOclosestPoint = normalize(relativePosSphere - closestPoint);
	relativePosSphereTOclosestPoint *= radius;

	vec3 pointMaxDepth = relativePosSphere + relativePosSphereTOclosestPoint;

	if (radius - length(relativePosSphere - closestPoint)>0)
	{
		vec3 p_CubeSpace = (pointMaxDepth + closestPoint) / 2.0f;
		vec3 n_CubeSpace = closestPoint - pointMaxDepth;

		vec3 p_WorldSpace = vec3(toWorldSpace*vec4(p_CubeSpace, 1.0));
		vec3 n_WorldSpace = vec3(toWorldSpace*vec4(n_CubeSpace, 1.0));

		result = new Contact();
		result->normal = n_WorldSpace;
		result->position = p_WorldSpace;
	}

	return result;
}
Contact* CubeDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2)
{
	return nullptr;
}

Contact * CubeDetectionComponent::getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent * detComp2)
{

	
}
