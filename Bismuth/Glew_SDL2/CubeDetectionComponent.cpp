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

	mat4 rotMat = rotate(rot1.x, vec3(1, 0, 0)) *rotate(rot1.y, vec3(0, 1, 0))*rotate(rot1.z, vec3(0, 0, 1));
	mat4 transMat = translate(pos1);
	mat4 invRotMat = rotate(-rot1.z, vec3(0, 0, 0)) * rotate(-rot1.y, vec3(0, 1, 0))*rotate(-rot1.x, vec3(1, 0, 0));
	mat4 invTransMat = translate(-pos1);

	mat4 rotMatPlane = rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1));
	mat4 invRotMatPlane = rotate(-rot2.z, vec3(0, 0, 0)) * rotate(-rot2.y, vec3(0, 1, 0))*rotate(-rot2.x, vec3(1, 0, 0));
	
	// Normale du plan
	vec4 planeNorm = rotMatPlane*vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// vecteurs orthogonaux quelconques du plan
	vec3 planeVX = vec3(rotMatPlane*vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vec3 planeVY = vec3(rotMatPlane*vec4(0.0f, 1.0f, 0.0f, 1.0f));



	planeNorm *= invRotMat * planeNorm;

	vec4 pos2CubeRef = invRotMat*invTransMat*vec4(pos2, 1.0f);

	vec3 normal;
	

	for (int i = 0; i < 8; i++)
	{
		vec3 v = vertices[i] - vec3(pos2CubeRef);

		// Projete orthogonal de v sur le plan
		vec3 pv = dot(v, planeVX)*planeVX + dot(v, planeVY)*planeVY;
		normal = pv - v;
		vec3 pvPlaneRef = vec3(invRotMatPlane*rotMat*vec4(pv, 1.0f));

		if (dot(normal, vertices[i]) > 0 && pvPlaneRef.x > -mSizeX/2 && pvPlaneRef.x < mSizeX/2
			&& pvPlaneRef.y > -mSizeY / 2 && pvPlaneRef.y < mSizeY / 2
			&& pvPlaneRef.z > -mSizeZ / 2 && pvPlaneRef.z < mSizeZ / 2)
		{
			Contact *contact = new Contact;
			contact->normal = vec3(rotMat*vec4(normal, 1.0f));
			contact->position = vec3(transMat*rotMat*vec4(vertices[i], 1.0f));
			contact->who = nullptr;

			return contact;
		}
		else
		{
			return nullptr;
		}

	}
}
