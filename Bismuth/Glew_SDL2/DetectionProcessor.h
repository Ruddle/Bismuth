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

	Contact* cubeToRay(CubeDetectionComponent cube, RayDetectionComponent ray);
	Contact* cubeToSphere(CubeDetectionComponent cube, SphereDetectionComponent sphere);
	Contact* cubeToPlane(CubeDetectionComponent cube, PlaneDetectionComponent plane);
	Contact* cubeToCube(CubeDetectionComponent cube, CubeDetectionComponent cube2 );

	Contact* planeToRay(PlaneDetectionComponent plane, RayDetectionComponent ray);
	Contact* planeToSphere(PlaneDetectionComponent plane, SphereDetectionComponent sphere);
	Contact* planeToPlane(PlaneDetectionComponent plane, PlaneDetectionComponent plane2);

	Contact* sphereToRay(SphereDetectionComponent sphere, RayDetectionComponent ray);
	Contact* sphereToSphere(SphereDetectionComponent sphere, SphereDetectionComponent sphere2);

	Contact* rayToRay(RayDetectionComponent ray, RayDetectionComponent ray2);

	

};

