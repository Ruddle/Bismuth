#pragma once
class Observer_dot
{
public:
	Observer_dot();
	~Observer_dot();

	virtual void Action_dot(int direction) = 0;
};

