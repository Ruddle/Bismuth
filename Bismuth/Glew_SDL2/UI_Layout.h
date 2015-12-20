#pragma once
#include "glm.hpp"
#include "UI_Element.h"
class UI_Layout
{
public:
	UI_Layout();
	~UI_Layout();

	virtual glm::vec2 getPosition(UI_Element const& e) = 0;


};

