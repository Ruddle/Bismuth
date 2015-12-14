#include "SliderController.h"



SliderController::SliderController(Slider* slider) : mSlider(slider)
{
	mSlider->addObserver(this);
}


SliderController::~SliderController()
{
}
