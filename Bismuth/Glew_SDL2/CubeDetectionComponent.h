#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"
#include "glm.hpp"


class CubeDetectionComponent : public DetectionComponent
{

public:
	CubeDetectionComponent(float sizeX, float sizeY, float sizeZ);
	~CubeDetectionComponent();

	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2);

	int getShape() { return CUBE; }

private:
	float mSizeX;
	float mSizeY;
	float mSizeZ;
};