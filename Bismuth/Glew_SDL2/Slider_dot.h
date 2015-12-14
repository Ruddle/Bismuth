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
#include "Observer_button.h"
class Slider_dot
{
public:
	Slider_dot();
	~Slider_dot();

	void addObserver(Observer_button* observer) { mObservers.insert(observer); }

protected:
	UI_box* mUI_box;
private:
	Entity2D* mEntity;
	std::unordered_set<Observer_button*> mObservers;
};

