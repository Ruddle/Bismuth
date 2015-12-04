#include "Button.h"






Button::Button(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size):
	Panel(em, rm, input, resolution, leftBottom, size)
{
	
}

Button::~Button()
{
}
