#pragma once

#include "glew.h"
#include "SDL_image.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"
#include "Texture.h"
#include "Entity2D.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"
#include "EntityManager.h"
#include "UI_box.h"
#include "Slider_dot.h"
#include "Slider_bar.h"
#include "Observer_bar.h"
#include "Observer_dot.h"
#include "Observer_float.h"

class Slider: public Observer_bar, public Observer_dot
{
public:
	Slider(EntityManager* em, ResourcesManager* rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Slider();

	void Action_bar();
	void Action_dot();

	float getValue() { return mValue; }

	void notify();

	void addObserver(Observer_float* observer) { mObservers.insert(observer); }
private:
	Slider_dot* mDot;
	Slider_bar* mBar;
	double mValue;
	double mMax;
	double mMin;
	double mStep;
	std::unordered_set<Observer_float*> mObservers;
};

