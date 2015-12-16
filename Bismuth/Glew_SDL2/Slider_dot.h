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
#include "Observer_dot.h"
#include "Observer_float.h"
#include "Observer_Slider.h"

class Slider_dot : public Observer_Slider, public Observer_UI_box
{
public:
	Slider_dot(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Slider_dot();

	void addObserver(Observer_dot* observer) { mObservers.insert(observer); }

	void onHover(glm::vec2 mouse);
	void onUnHover(glm::vec2 mouse);
	void onClick(glm::vec2 mouse);
	void onUnClick(glm::vec2 mouse);
	void onSelect(glm::vec2 mouse);
	void onDeSelect(glm::vec2 mouse);
	void onDrag(glm::vec2 mouse);

	void notify(int direction);

	void Action(float value, float min, float max, float step);

protected:
	UI_box* mUI_box;
private:
	Entity2D* mEntity;

	glm::vec2 mResolution;
	glm::vec2 mLeftBottom;
	glm::vec2 mSize;
	bool mIsDragged;

	std::unordered_set<Observer_dot*> mObservers;
};

