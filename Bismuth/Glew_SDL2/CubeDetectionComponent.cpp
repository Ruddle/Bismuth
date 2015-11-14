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
	float radius  =sqrt(( (SphereDetectionComponent*) detComp2)->getRadius2());

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

		vec3 p_WorldSpace =vec3( toWorldSpace*vec4(p_CubeSpace, 1.0));
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

		if (dot(normal, vertices[i]) > 0 && pvPlaneRef.x > -mSizeX / 2 && pvPlaneRef.x < mSizeX / 2
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
