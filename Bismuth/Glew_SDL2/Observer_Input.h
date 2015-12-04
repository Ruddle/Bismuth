#pragma once
#include "glm.hpp"
class Observer_Input
{
public:
	Observer_Input();
	~Observer_Input();

	virtual void move(glm::vec2 mouse, glm::vec2 mouseRelative ) = 0;
	virtual void select(glm::vec2 mouse) = 0;
	virtual void deselect(glm::vec2 mouse) = 0;

};

