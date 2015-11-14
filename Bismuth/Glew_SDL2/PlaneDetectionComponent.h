#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"

class PlaneDetectionComponent : public DetectionComponent
{

public:

	PlaneDetectionComponent(float sizeX, float sizeY);
	~PlaneDetectionComponent();

	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2);

	int getShape() { return PLANE; }

private:

	float mSizeX;
	float mSizeY;
};