#include "ButtonController.h"



ButtonController::ButtonController(Button* button) : mButton(button)
{
	mButton->addObserver(this);
}


ButtonController::~ButtonController()
{
}
