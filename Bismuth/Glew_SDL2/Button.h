#pragma once
#include "Panel.h"
class Button : public Panel
{
public:
	Button(EntityManager* em, ResourcesManager* rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Button();

};

