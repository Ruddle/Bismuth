#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"
#include "CubeDetectionComponent.h"
#include "SphereDetectionComponent.h"
#include "PlaneDetectionComponent.h"

class SphereDetectionComponent : public DetectionComponent
{

public:
	SphereDetectionComponent(float radius2);
	~SphereDetectionComponent();
	
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, RayDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, SphereDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, CubeDetectionComponent *detComp2);
	Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, PlaneDetectionComponent *detComp2);

	int getShape() {return SPHERE;}
	float getRadius2() { return mRadius2; }

private:

	float mRadius2;



};