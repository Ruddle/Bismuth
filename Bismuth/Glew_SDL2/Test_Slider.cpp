#include "Test_Slider.h"



Test_Slider::Test_Slider(Slider* slider, float* value) : SliderController(slider),mValue(value)
{
}


Test_Slider::~Test_Slider()
{
}

void Test_Slider::Action(float value, float min, float max, float step)
{
	*mValue = value;

}

