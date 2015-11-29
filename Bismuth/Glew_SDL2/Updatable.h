#pragma once
#include "Entity.h"
class Updatable
{
public:
	Updatable();
	~Updatable();

	virtual void update(float elapsedTime) = 0;
	virtual Entity *getEntity() = 0;

};

