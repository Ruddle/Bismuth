#include "Button.h"

using namespace glm;

Button::Button(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size):
	Panel(em, rm, input, resolution, leftBottom, size) 
{
	mBox->addObserver(this);
	getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(0.0 / 4.0f, 1.0 / 4.0f));
}

Button::~Button()
{
	delete mLabel;
}

void Button::onHover(glm::vec2 mouse)
{
	if(!mBox->isSelected())
	getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(0.0 / 4.0f, 0.0 / 4.0f));
}

void Button::onUnHover(glm::vec2 mouse)
{
	if (!mBox->isSelected())
		getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(0.0 / 4.0f, 1.0 / 4.0f));
}

void Button::onClick(glm::vec2 mouse)
{
	notifyAction();
}

void Button::onSelect(glm::vec2 mouse)
{
	getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(1.0 / 4.0f, 1.0 / 4.0f));
}

void Button::onDeSelect(glm::vec2 mouse)
{
	getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(0.0 / 4.0f, 1.0 / 4.0f));
}

void Button::notifyAction()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->Action();
}