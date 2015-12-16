#pragma once
class Observer_Slider
{
public:
	Observer_Slider();
	~Observer_Slider();

	virtual void Action(float value,float min,float max,float step) = 0;
};

