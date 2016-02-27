#pragma once
#include "glew.h"
#include "SDL_image.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Texture.h"
#include "Entity2D.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"
#include "EntityManager.h"
#include "UI_box.h"
#include "Observer_button.h"
#include "Observer_bar.h"
class Slider_bar : public Observer_UI_box
{
public:
	Slider_bar(EntityManager * em, ResourcesManager * rm, Input * input, glm::vec2 resolution, glm::vec2 leftBottom, glm::vec2 size);
	~Slider_bar();

	void addObserver(Observer_bar* observer) { mObservers.insert(observer); }

	void onHover(glm::vec2 mouse);
	void onUnHover(glm::vec2 mouse);
	void onClick(glm::vec2 mouse);
	void onUnClick(glm::vec2 mouse);
	void onSelect(glm::vec2 mouse);
	void onDeSelect(glm::vec2 mouse);
	void onDrag(glm::vec2 mouse);

	void notify();

protected:
	UI_box* mUI_box;
private:
	Entity2D* mEntity;
	std::unordered_set<Observer_bar*> mObservers;
};

