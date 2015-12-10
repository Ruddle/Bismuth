#include "Button.h"

using namespace glm;

Button::Button(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size):
	Panel(em, rm, input, resolution, leftBottom, size) , mIsChecked(false) , mLastSelected(false) 
{
	
}

Button::~Button()
{
	delete mLabel;
}

void Button::update()
{
	if (getMainEntity()->getPhysicComponent()->isSelected() && !mLastSelected)
	{
		mLastSelected = true;
		mIsChecked = !mIsChecked;
	}

	if (!getMainEntity()->getPhysicComponent()->isSelected())
		mLastSelected = false;





	if( mIsChecked)
		getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(1.0 / 4.0f, 1.0 / 4.0f));
	else 
		getMainEntity()->getGraphicComponent()->setLeftBottom(vec2(0.0 / 4.0f, 1.0 / 4.0f));



}
