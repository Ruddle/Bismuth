#pragma once
#include "glm.hpp"
class PhysicComponent2D
{
public:
	PhysicComponent2D(glm::vec2 size,glm::vec2 position);
	~PhysicComponent2D();

	glm::vec2 getSize() { return mSize; }
	glm::vec2 getPosition() { return mPosition; }


private:

	glm::vec2 mSize;
	glm::vec2 mPosition; //left bottom 


};

