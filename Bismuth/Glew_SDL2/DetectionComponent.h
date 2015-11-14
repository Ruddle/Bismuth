#pragma once

#include <glm.hpp>
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"



class DetectionComponent
{
public :
    enum Shape {CUBE, SPHERE, RAY, PLANE};
   
	virtual Contact* getCollision(glm::vec3 pos1, glm::vec3 rot1, glm::vec3 pos2, glm::vec3 rot2, DetectionComponent *detComp2) = 0;
	virtual int getShape() = 0;


};
