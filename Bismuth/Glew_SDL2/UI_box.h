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
#include "Observer_UI_box.h"

class UI_box : public Observer_Input
{
public:

	UI_box(PhysicComponent2D* physicComponent);
	~UI_box();

	void move(glm::vec2 mouse, glm::vec2 mouseRelative);
	void click(glm::vec2 mouse);
	void unclick(glm::vec2 mouse);

	bool isSelected() { return mIsSelected; }
	bool isHovered() { return mIsHovered; }
	bool isClicked() { return mIsClicked; }

	void addObserver(Observer_UI_box* observer) { mObservers.insert(observer); }

	void notifyHover(glm::vec2 mouse);
	void notifyClick(glm::vec2 mouse);
	void notifySelected(glm::vec2 mouse);
	void notifyUnSelected(glm::vec2 mouse);
	void notifyUnHover(glm::vec2 mouse);

private:
	PhysicComponent2D* mPhysicComponent;
	std::unordered_set<Observer_UI_box*> mObservers;
	bool mIsClicked;
	bool mIsSelected;
	bool mIsHovered;


};

