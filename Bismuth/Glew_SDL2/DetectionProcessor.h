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

	Contact* detection(DetectionComponent::Shape const& a, DetectionComponent::Shape const& b,
	    glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* cubeToRay(CubeDetectionComponent const& cube, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* cubeToSphere(CubeDetectionComponent const& cube, SphereDetectionComponent const& sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* cubeToPlane(CubeDetectionComponent const& cube, PlaneDetectionComponent const& plane,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* cubeToCube(CubeDetectionComponent const& cube, CubeDetectionComponent const& cube2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2) ;

	Contact* planeToRay(PlaneDetectionComponent const& plane, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* planeToSphere(PlaneDetectionComponent const& plane, SphereDetectionComponent const& sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* planeToPlane(PlaneDetectionComponent const& plane, PlaneDetectionComponent const& plane2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* sphereToRay(SphereDetectionComponent const& sphere, RayDetectionComponent const& ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* sphereToSphere(SphereDetectionComponent const& sphere, SphereDetectionComponent const& sphere2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* rayToRay(RayDetectionComponent const& ray, RayDetectionComponent const& ray2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	

};

