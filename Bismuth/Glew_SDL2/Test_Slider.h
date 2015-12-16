#pragma once
#include "SliderController.h"
class Test_Slider : public SliderController
{
public:
	Test_Slider(Slider* slider,float* value);
	~Test_Slider();

	void Action(float value, float min, float max, float step);
private:
	float* mValue;

};

