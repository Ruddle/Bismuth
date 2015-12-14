#pragma once
#include "glm.hpp"
class Observer_Input
{
public:
	Observer_Input();
	~Observer_Input();

	virtual void move(glm::vec2 mouse, glm::vec2 mouseRelative ) = 0;
	virtual void click(glm::vec2 mouse) = 0;
	virtual void unclick(glm::vec2 mouse) = 0;

};

