#include "DetectionProcessor.h"

using namespace glm;


DetectionProcessor::DetectionProcessor()
{
}


DetectionProcessor::~DetectionProcessor()
{
}

Contact * DetectionProcessor::detection(DetectionComponent const& a, DetectionComponent const& b,
	glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2)
{
	

	switch (a.getShape()) {

	case DetectionComponent::CUBE:
		
		switch (b.getShape()) {
		case DetectionComponent::CUBE:
			return cubeToCube(a, b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::PLANE:
			// Code
			break;

		case DetectionComponent::SPHERE:
			// Code
			break;

		case DetectionComponent::RAY:
			// Code
			break;

		default:
			// Code
			break;
		}
		break;

	case DetectionComponent::PLANE:
		

		switch (b.getShape()) {
		case DetectionComponent::CUBE:
			// Code
			break;

		case DetectionComponent::PLANE:
			// Code
			break;

		case DetectionComponent::SPHERE:
			// Code
			break;

		case DetectionComponent::RAY:
			// Code
			break;

		default:
			// Code
			break;
		}

		break;

	case DetectionComponent::SPHERE:
		switch (b.getShape()) {
		case DetectionComponent::CUBE:
			// Code
			break;

		case DetectionComponent::PLANE:
			// Code
			break;

		case DetectionComponent::SPHERE:
			// Code
			break;

		case DetectionComponent::RAY:
			// Code
			break;

		default:
			// Code
			break;
		}
		break;

	case DetectionComponent::RAY:
		switch (b.getShape()) {
		case DetectionComponent::CUBE:
			// Code
			break;

		case DetectionComponent::PLANE:
			// Code
			break;

		case DetectionComponent::SPHERE:
			// Code
			break;

		case DetectionComponent::RAY:
			// Code
			break;

		default:
			// Code
			break;
		}
		break;


	default:
		// Code
		break;
	}
	
	
	
	
	return nullptr;
}

Contact * DetectionProcessor::cubeToRay(CubeDetectionComponent const& cube, RayDetectionComponent const& ray,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::cubeToSphere(CubeDetectionComponent const& cube, SphereDetectionComponent const& sphere,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	Contact* result = nullptr;
	vec3 half = cube.getSize()/2.0f;
	mat4 toWorldSpace = rotate(rot1.x, vec3(1, 0, 0)) *rotate(rot1.y, vec3(0, 1, 0))*rotate(rot1.z, vec3(0, 0, 1));
	mat4 toCubeSpace = inverse(toWorldSpace);

	vec3 relativePosSphere = vec3(toCubeSpace*vec4(pos2, 1));
	float radius = sqrt(sphere.getRadius2());

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

Contact * DetectionProcessor::cubeToPlane(CubeDetectionComponent const& cube, PlaneDetectionComponent const& plane,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
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

Contact * DetectionProcessor::cubeToCube(CubeDetectionComponent const& cube, CubeDetectionComponent const& cube2,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToRay(PlaneDetectionComponent const& plane, RayDetectionComponent const& ray,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToSphere(PlaneDetectionComponent const& plane, SphereDetectionComponent const& sphere,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToPlane(PlaneDetectionComponent const& plane, PlaneDetectionComponent const& plane2,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::sphereToRay(SphereDetectionComponent const& sphere, RayDetectionComponent const& ray,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	vec3 &s = pos1;
	vec3 L1 = pos2;
	vec3 L1L2 = normalize(vec3(rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1)) * vec4(1, 0, 0, 1)));
	vec3 sL1 = L1 - s;

	float u = dot(sL1, sL1) - sphere.getRadius2();
	float v = 2 * dot(sL1, L1L2);
	float w = dot(L1L2, L1L2);

	float discri = pow(v, 2) - 4 * u*w;
	if (0 > discri) // Pas de racine réelle => pas d'intersection
		return nullptr;

	Contact* result = new Contact;

	float t1 = (1 / (2 * w)) * (-v + sqrt(discri));
	float t2 = (1 / (2 * w)) * (-v - sqrt(discri));

	vec3 contactPosition1 = L1 + L1L2*t1;
	vec3 contactPosition2 = L1 + L1L2*t2;

	if (glm::distance(contactPosition1, L1) < glm::distance(contactPosition1, L1))
		result->position = contactPosition1;
	else
		result->position = contactPosition2;

	result->normal = result->position - pos1;


	return result;

}

Contact * DetectionProcessor::sphereToSphere(SphereDetectionComponent const& sphere, SphereDetectionComponent const& sphere2,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	float radius2_2 = sphere2.getRadius2;

	float r1 = sqrt(sphere.getRadius2);
	float r2 = sqrt(radius2_2);

	if (r1 + r2 <= length(pos1 - pos2))
		return nullptr;

	Contact* result = new Contact;



	result->position = (r2*pos1 + r1*pos2) / (r1 + r2);
	result->normal = normalize(pos2 - pos1)*((r2 + r1) - length(pos2 - pos1));

	return result;
}

Contact * DetectionProcessor::rayToRay(RayDetectionComponent const& ray, RayDetectionComponent const& ray2,
	glm::vec3 pos1, glm::vec3 rot1,
	glm::vec3 pos2, glm::vec3 rot2)
{
	return nullptr;
}

