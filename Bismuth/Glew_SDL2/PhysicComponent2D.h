#pragma once
#include "glm.hpp"
#include "Observer_Input.h"

#include <iostream>
class PhysicComponent2D 
{
public:
	PhysicComponent2D(glm::vec2 size,glm::vec2 position);
	~PhysicComponent2D();
	glm::vec2 getSize() { return mSize; }
	glm::vec2 getPosition() { return mPosition; }

	void setPosition(glm::vec2 position) { mPosition = position; }
	void setSize(glm::vec2 size) { mSize = size; }

	bool contain(glm::vec2 mouse);

private:

	glm::vec2 mSize;
	glm::vec2 mPosition; //left bottom 
};

