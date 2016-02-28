#pragma once
class Updatable
{
public:
	Updatable();
	~Updatable();

	virtual void update(float elapsedTime) = 0;

};

