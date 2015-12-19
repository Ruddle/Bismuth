#include "ButtonController_int.h"





ButtonController_int::ButtonController_int(Button * button, int * ptr) : mPtr(ptr) , ButtonController(button)
{
}

ButtonController_int::~ButtonController_int()
{
}

void ButtonController_int::Action()
{
	*mPtr = mButton->isChecked();
}
