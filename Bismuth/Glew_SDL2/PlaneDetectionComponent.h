#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"

class PlaneDetectionComponent : public DetectionComponent
{

public:

	PlaneDetectionComponent(float sizeX, float sizeY);
	~PlaneDetectionComponent();

	Contact* getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);
	Contact* getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);
	Contact* getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);
	Contact* getCollisionOnPlane(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);

	int getShape() { return PLANE; }
	float getSizeX() { return mSizeX; }
	float getSizeY() { return mSizeY; }


private:

	float mSizeX;
	float mSizeY;
};