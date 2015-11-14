#pragma once

#include <glm.hpp>
#include "Contact.h"
#include "glm\gtx\rotate_vector.hpp"



class DetectionComponent
{
public :
    enum Shape {CUBE, SPHERE, RAY, PLANE};
   
	virtual Shape getShape() const = 0;

};
