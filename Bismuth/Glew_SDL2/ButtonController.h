#pragma once
#include "Button.h"
class ButtonController : public Observer_button
{
public:
	ButtonController(Button* button);
	~ButtonController();

protected :
	Button* mButton;
};

