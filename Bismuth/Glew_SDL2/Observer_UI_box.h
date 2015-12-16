#pragma once
#include "glm.hpp"
class Observer_UI_box
{
public:
	Observer_UI_box();
	~Observer_UI_box();


	
	virtual void onClick(glm::vec2 mouse) = 0;
	virtual void onUnClick(glm::vec2 mouse) = 0;
	virtual void onSelect(glm::vec2 mouse) = 0;
	virtual void onDeSelect(glm::vec2 mouse) = 0;
	virtual void onHover(glm::vec2 mouse) = 0;
	virtual void onUnHover(glm::vec2 mouse) = 0;
	virtual void onDrag(glm::vec2 mouse) = 0;
};

