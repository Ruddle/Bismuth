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

	Contact* detection(DetectionComponent::Shape a, DetectionComponent::Shape b,
	    glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* cubeToRay(CubeDetectionComponent cube, RayDetectionComponent ray, 
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* cubeToSphere(CubeDetectionComponent cube, SphereDetectionComponent sphere, 
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* cubeToPlane(CubeDetectionComponent cube, PlaneDetectionComponent plane,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* cubeToCube(CubeDetectionComponent cube, CubeDetectionComponent cube2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2) ;

	Contact* planeToRay(PlaneDetectionComponent plane, RayDetectionComponent ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* planeToSphere(PlaneDetectionComponent plane, SphereDetectionComponent sphere,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* planeToPlane(PlaneDetectionComponent plane, PlaneDetectionComponent plane2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* sphereToRay(SphereDetectionComponent sphere, RayDetectionComponent ray,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);
	Contact* sphereToSphere(SphereDetectionComponent sphere, SphereDetectionComponent sphere2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	Contact* rayToRay(RayDetectionComponent ray, RayDetectionComponent ray2,
		glm::vec3 pos1, glm::vec3 rot1,
		glm::vec3 pos2, glm::vec3 rot2);

	

};

