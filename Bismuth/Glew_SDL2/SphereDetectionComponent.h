#pragma once

#include "DetectionComponent.h"
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"

class SphereDetectionComponent : public DetectionComponent
{

public:
	SphereDetectionComponent(float radius2);
	~SphereDetectionComponent();
	
	Contact* getCollisionOnRay(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);
	Contact* getCollisionOnSphere(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);
	Contact* getCollisionOnCube(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2);

	int getShape() {return SPHERE;}

private:

	float mRadius2;



};