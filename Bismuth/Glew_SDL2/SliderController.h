#pragma once
#include "Observer_button.h"
#include "Slider.h"
class SliderController : public Observer_float
{
public:
	SliderController(Slider* slider);
	~SliderController();
protected :
	Slider* mSlider;
};

