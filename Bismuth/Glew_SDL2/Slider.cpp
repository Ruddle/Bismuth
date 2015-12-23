#include "Slider.h"



using namespace glm;

Slider::Slider(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size)
{
	mValue = 0.5;
	mMin = 0;
	mMax = 1;
	mStep = 0.05;


	mBar = new Slider_bar(em, rm, input, resolution, leftBottom, size);
	mDot = new Slider_dot(em, rm, input, resolution, leftBottom, size);

	this->addObserver(mDot);
	mBar->addObserver(this);
	mDot->addObserver(this);

}

Slider::~Slider()
{
}

void Slider::Action_bar()
{

	
}

void Slider::Action_dot(int direction)
{
	mValue += direction*mStep;
	mValue = clamp(mValue, mMin, mMax);
	notify();
}

void Slider::notify()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->Action(float(mValue),float(mMin),float(mMax),float(mStep) );

}
