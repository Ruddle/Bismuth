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

	Contact* detection(Shape a, Shape b, glm::vec3, glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2);

	Contact* cubeToRay();
	Contact* cubeToSphere();
	Contact* cubeToPlane();
	Contact* cubeToCube();

	Contact* planeToRay();
	Contact* planeToSphere();
	Contact* planeToPlane();

	Contact* sphereToRay();
	Contact* sphereToSphere();

	Contact* rayToRay();

	

};

