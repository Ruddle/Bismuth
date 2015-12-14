#pragma once
class Observer_float
{
public:
	Observer_float();
	~Observer_float();

	virtual void Action(float x) = 0;
};

