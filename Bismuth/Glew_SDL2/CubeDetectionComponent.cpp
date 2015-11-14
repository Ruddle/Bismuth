#include "CubeDetectionComponent.h"

using namespace glm;

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

Contact * CubeDetectionComponent::getCollisionOnPlane(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent * detComp2)
{

	vec3 vertices[8] = { vec3(-mSizeX / 2, -mSizeY / 2, -mSizeZ / 2), vec3(mSizeX / 2, -mSizeY / 2, -mSizeZ / 2),
						vec3(mSizeX / 2, mSizeY / 2, -mSizeZ / 2), vec3(-mSizeX / 2, mSizeY / 2, -mSizeZ / 2),
						vec3(-mSizeX / 2, -mSizeY / 2, mSizeZ / 2), vec3(mSizeX / 2, -mSizeY / 2, mSizeZ / 2),
						vec3(mSizeX / 2, mSizeY / 2, mSizeZ / 2), vec3(-mSizeX / 2, mSizeY / 2, mSizeZ / 2) };

	mat4 invRotMat = rotate(-rot1.z, vec3(0, 0, 0)) * rotate(-rot1.y, vec3(0, 1, 0))*rotate(-rot1.x, vec3(1, 0, 0))/**translate(-pos1)*/;

	
	// Normale du plan
	vec4 planeNorm = rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1))*vec4(0.0f, 0.0f, 1.0f, 1.0f);
	planeNorm *= invRotMat * planeNorm;

	for (int i = 0; i < 8; i++)
	{
		/*float dist = dot(planeNorm, )*/
	}

	return nullptr;
}
