#include "DetectionProcessor.h"

#include <iostream>

using namespace glm;


DetectionProcessor::DetectionProcessor()
{
}


DetectionProcessor::~DetectionProcessor()
{
}

Contact * DetectionProcessor::detection(DetectionComponent * a, DetectionComponent * b,
	glm::vec3 const& pos1, glm::vec3 const& rot1, glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	

	switch (a->getShape()) {

	case DetectionComponent::CUBE:
		
		switch (b->getShape()) {
		case DetectionComponent::CUBE:
			return cubeToCube((CubeDetectionComponent*)a, (CubeDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::PLANE:
			return cubeToPlane((CubeDetectionComponent*)a, (PlaneDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::SPHERE:
			return cubeToSphere((CubeDetectionComponent*)a, (SphereDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::RAY:
			return cubeToRay((CubeDetectionComponent*)a, (RayDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		default:
			// Code
			break;
		}
		break;

	case DetectionComponent::PLANE:
		

		switch (b->getShape()) {
		case DetectionComponent::CUBE:
			return  reverse(cubeToPlane((CubeDetectionComponent*)b, (PlaneDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::PLANE:
			return planeToPlane((PlaneDetectionComponent*)a, (PlaneDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::SPHERE:
			return planeToSphere((PlaneDetectionComponent*)a, (SphereDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::RAY:
			return planeToRay((PlaneDetectionComponent*)a, (RayDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		default:
			// Code
			break;
		}

		break;

	case DetectionComponent::SPHERE:
		switch (b->getShape()) {
		case DetectionComponent::CUBE:
			return  reverse(cubeToSphere((CubeDetectionComponent*)b, (SphereDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::PLANE:
			return  reverse(planeToSphere((PlaneDetectionComponent*)b, (SphereDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::SPHERE:
			return sphereToSphere((SphereDetectionComponent*)a, (SphereDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		case DetectionComponent::RAY:
			return sphereToRay((SphereDetectionComponent*)a, (RayDetectionComponent*)b, pos1, rot1, pos2, rot2);
			break;

		default:
			// Code
			break;
		}
		break;

	case DetectionComponent::RAY:
		switch (b->getShape()) {
		case DetectionComponent::CUBE:
			return  reverse(cubeToRay((CubeDetectionComponent*)b, (RayDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::PLANE:
			return  reverse(planeToRay((PlaneDetectionComponent*)b, (RayDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::SPHERE:
			return  reverse(cubeToSphere((CubeDetectionComponent*)b, (SphereDetectionComponent*)a, pos2, rot2, pos1, rot1));
			break;

		case DetectionComponent::RAY:
			return rayToRay((RayDetectionComponent*)a, (RayDetectionComponent*)b, pos1, rot1, pos2, rot2);
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

Contact * DetectionProcessor::cubeToRay(CubeDetectionComponent * cube, RayDetectionComponent * ray,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::cubeToSphere(CubeDetectionComponent * cube, SphereDetectionComponent * sphere,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	Contact* result = nullptr;
	vec3 half = cube->getSize()/2.0f;
	mat4 toWorldSpace = translate(pos1)*rotate(rot1.x, vec3(1, 0, 0)) *rotate(rot1.y, vec3(0, 1, 0))*rotate(rot1.z, vec3(0, 0, 1));
	mat4 toCubeSpace = inverse(toWorldSpace);

	vec3 relativePosSphere = vec3(toCubeSpace*vec4(pos2, 1));
	float radius = sqrt(sphere->getRadius2());

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




	if (radius - length(relativePosSphere - closestPoint)>0)
	{
		vec3 relativePosSphereTOclosestPoint = -normalize(relativePosSphere - closestPoint);
		relativePosSphereTOclosestPoint *= radius;

		vec3 pointMaxDepth = relativePosSphere + relativePosSphereTOclosestPoint;

		/*vec3 p_CubeSpace = (pointMaxDepth + closestPoint) / 2.0f;
		vec3 n_CubeSpace = closestPoint - pointMaxDepth;

		vec3 p_WorldSpace = vec3(toWorldSpace*vec4(p_CubeSpace, 1.0));
		vec3 n_WorldSpace = vec3(toWorldSpace*vec4(n_CubeSpace, 1.0));*/

		vec3 closestPoint_WorldSpace = vec3(toWorldSpace*vec4(closestPoint, 1.0));
		vec3 pointMaxDepth_WorldSpace = vec3(toWorldSpace*vec4(pointMaxDepth, 1.0));


		vec3 p_WorldSpace = (pointMaxDepth + closestPoint) / 2.0f;
		vec3 n_WorldSpace = closestPoint - pointMaxDepth;

		result = new Contact();
		result->normal = n_WorldSpace;
		result->position = p_WorldSpace;
	}

	return result;
}

Contact * DetectionProcessor::cubeToPlane(CubeDetectionComponent * cube, PlaneDetectionComponent * plane,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	vec3 s = cube->getSize();

	vec3 vertices[8] = { vec3(-s.x / 2, -s.y / 2, -s.z / 2), vec3(s.x / 2, -s.y / 2, -s.z / 2),
		vec3(s.x / 2, s.y / 2, -s.z / 2), vec3(-s.x / 2, s.y / 2, -s.z / 2),
		vec3(-s.x / 2, -s.y / 2, s.z / 2), vec3(s.x / 2, -s.y / 2, s.z / 2),
		vec3(s.x / 2, s.y / 2, s.z / 2), vec3(-s.x / 2, s.y / 2, s.z / 2) };

	mat4 rotMatCube = rotate(rot1.x, vec3(1, 0, 0)) *rotate(rot1.y, vec3(0, 1, 0))*rotate(rot1.z, vec3(0, 0, 1));
	mat4 transMatCube = translate(pos1);
	mat4 invRotMatCube = rotate(-rot1.z, vec3(0, 0, 0)) * rotate(-rot1.y, vec3(0, 1, 0))*rotate(-rot1.x, vec3(1, 0, 0));
	mat4 invTransMatCube = translate(-pos1);

	mat4 rotMatPlane = rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1));
	mat4 invRotMatPlane = rotate(-rot2.z, vec3(0, 0, 0)) * rotate(-rot2.y, vec3(0, 1, 0))*rotate(-rot2.x, vec3(1, 0, 0));

	// Normale du plan
	vec4 planeNorm = rotMatPlane*vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// vecteurs orthogonaux quelconques du plan
	vec3 planeVX = vec3(invRotMatCube*rotMatPlane*vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vec3 planeVY = vec3(invRotMatCube*rotMatPlane*vec4(0.0f, 1.0f, 0.0f, 1.0f));



	planeNorm *= invRotMatCube * planeNorm;

	vec4 pos2CubeRef = invRotMatCube*invTransMatCube*vec4(pos2, 1.0f);

	vec3 normal;

	//std::cout << "-----" << std::endl;

	for (int i = 0; i < 8; i++)
	{
		vec3 v = vertices[i] - vec3(pos2CubeRef);

		// Projete orthogonal de v sur le plan
		vec3 pv = dot(v, planeVX)*planeVX + dot(v, planeVY)*planeVY;
		normal = pv - v;
		vec3 pvPlaneRef = vec3(invRotMatPlane*rotMatCube*vec4(pv, 1.0f));

		//std::cout << i << " : " << dot(normal, vertices[i]) << std::endl;

		if (dot(normal, vertices[i]) > 0 && pvPlaneRef.x > -s.x / 2 && pvPlaneRef.x < s.x / 2
			&& pvPlaneRef.y > -s.y / 2 && pvPlaneRef.y < s.y / 2
			&& pvPlaneRef.z > -s.z / 2 && pvPlaneRef.z < s.z / 2)
		{
			Contact *contact = new Contact;
			contact->normal = vec3(rotMatCube*vec4(normal, 1.0f));
			contact->position = vec3(transMatCube*rotMatCube*vec4(vertices[i], 1.0f));
			contact->who = nullptr;

			return contact;
		}
	}
	return nullptr;
}

Contact * DetectionProcessor::cubeToCube(CubeDetectionComponent * cube, CubeDetectionComponent * cube2,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToRay(PlaneDetectionComponent * plane, RayDetectionComponent * ray,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToSphere(PlaneDetectionComponent * plane, SphereDetectionComponent * sphere,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::planeToPlane(PlaneDetectionComponent * plane, PlaneDetectionComponent * plane2,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

Contact * DetectionProcessor::sphereToRay(SphereDetectionComponent * sphere, RayDetectionComponent * ray,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	vec3 s = pos1;
	vec3 L1 = pos2;
	vec3 L1L2 = normalize(vec3(rotate(rot2.x, vec3(1, 0, 0)) *rotate(rot2.y, vec3(0, 1, 0))*rotate(rot2.z, vec3(0, 0, 1)) * vec4(1, 0, 0, 1)));
	vec3 sL1 = L1 - s;

	float u = dot(sL1, sL1) - sphere->getRadius2();
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

Contact * DetectionProcessor::sphereToSphere(SphereDetectionComponent * sphere, SphereDetectionComponent * sphere2,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	float radius2_2 = sphere2->getRadius2();

	float r1 = sqrt(sphere->getRadius2());
	float r2 = sqrt(radius2_2);

	if (r1 + r2 <= length(pos1 - pos2))
		return nullptr;

	Contact* result = new Contact;



	result->position = (r2*pos1 + r1*pos2) / (r1 + r2);
	result->normal = normalize(pos2 - pos1)*((r2 + r1) - length(pos2 - pos1));

	return result;
}

Contact * DetectionProcessor::rayToRay(RayDetectionComponent * ray, RayDetectionComponent * ray2,
	glm::vec3 const& pos1, glm::vec3 const& rot1,
	glm::vec3 const& pos2, glm::vec3 const& rot2)
{
	return nullptr;
}

