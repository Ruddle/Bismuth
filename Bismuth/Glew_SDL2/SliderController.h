#pragma once
#include "Observer_button.h"
#include "Slider.h"
class SliderController : public Observer_Slider
{
public:
	SliderController(Slider* slider);
	~SliderController();
protected :
	Slider* mSlider;
};

