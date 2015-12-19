#pragma once
#include "ButtonController.h"
#include "Misc.h"
class ButtonController_int : public ButtonController
{
public:

	ButtonController_int(Button * button, int * ptr);
	~ButtonController_int();

	void Action();

private:
	int * mPtr;

};

