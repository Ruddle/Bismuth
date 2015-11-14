#pragma once
#include "DetectionComponent.h"
#include "RayDetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "PlaneDetectionComponent.h"
#include "CubeDetectionComponent.h"

class DetectionProcessor
{
public:
	DetectionProcessor();
	~DetectionProcessor();

	static Contact* detection(DetectionComponent const& a, DetectionComponent const& b,
	    glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* cubeToRay(CubeDetectionComponent const& cube, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* cubeToSphere(CubeDetectionComponent const& cube, SphereDetectionComponent const& sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* cubeToPlane(CubeDetectionComponent const& cube, PlaneDetectionComponent const& plane,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* cubeToCube(CubeDetectionComponent const& cube, CubeDetectionComponent const& cube2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2) ;

	static Contact* planeToRay(PlaneDetectionComponent const& plane, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* planeToSphere(PlaneDetectionComponent const& plane, SphereDetectionComponent const& sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* planeToPlane(PlaneDetectionComponent const& plane, PlaneDetectionComponent const& plane2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* sphereToRay(SphereDetectionComponent const& sphere, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	static Contact* sphereToSphere(SphereDetectionComponent const& sphere, SphereDetectionComponent const& sphere2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	static Contact* rayToRay(RayDetectionComponent const& ray, RayDetectionComponent const& ray2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	

};

