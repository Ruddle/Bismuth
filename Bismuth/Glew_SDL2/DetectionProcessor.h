#pragma once
#include "DetectionComponent.h"
#include "RayDetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "PlaneDetectionComponent.h"
#include "CubeDetectionComponent.h"
#include "PhysicComponent.h"
#include "glm.hpp"

class DetectionProcessor
{
public:
	DetectionProcessor();
	~DetectionProcessor();

	static Contact* detection(DetectionComponent * a, DetectionComponent * b,
	    glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* cubeToRay(CubeDetectionComponent * cube, RayDetectionComponent * ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* cubeToSphere(CubeDetectionComponent * cube, SphereDetectionComponent * sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* cubeToPlane(CubeDetectionComponent * cube, PlaneDetectionComponent * plane,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* cubeToCube(CubeDetectionComponent * cube, CubeDetectionComponent * cube2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2) ;

	static Contact* planeToRay(PlaneDetectionComponent * plane, RayDetectionComponent * ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* planeToSphere(PlaneDetectionComponent * plane, SphereDetectionComponent * sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* planeToPlane(PlaneDetectionComponent * plane, PlaneDetectionComponent * plane2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* sphereToRay(SphereDetectionComponent * sphere, RayDetectionComponent * ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* sphereToSphere(SphereDetectionComponent * sphere, SphereDetectionComponent * sphere2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* rayToRay(RayDetectionComponent * ray, RayDetectionComponent * ray2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

private :

	static Contact* reverse(Contact* c) { if (c == nullptr) return nullptr; c->normal = -c->normal; return c; }

};

